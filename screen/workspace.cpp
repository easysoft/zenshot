/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

#include "workspace.h"

#include "screen/shotarea/areacreatetool.h"
#include "screen/shotarea/areamovetool.h"
#include "screen/shotarea/areahandletool.h"
#include "screen/movetool.h"
#include "screen/handletool.h"
#include "core/utils.h"
#include "stores/localstore.h"

#include "tools/linecreatetool.h"
#include "tools/rectcreatetool.h"
#include "tools/ellipsecreatetool.h"
#include "tools/arrowcreatetool.h"
#include "tools/curvecreatetool.h"
#include "tools/textcreatetool.h"
#include "tools/mosaiccreatetool.h"

#include "properties/arrowbar.h"
#include "properties/curvebar.h"
#include "properties/ellipsebar.h"
#include "properties/linebar.h"
#include "properties/mosaicbar.h"
#include "properties/rectanglebar.h"
#include "properties/textbar.h"

#include "spdlogwrapper.hpp"

#include "core/useroper.h"
#include "commands/deletecommand.h"
#include "commands/propscommand.h"
#include "stores/memorystore.h"
#include "core/gparams.h"
#include "core/gscale.h"

#include <QPainter>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QPalette>
#include <QFrame>
#include <QLabel>
#include <QDateTime>
#include <QFileDialog>
#include <QApplication>
#include <QClipboard>
#include <QFileInfo>
#include <QtMath>
#include <QDir>
#include <QDebug>

#ifdef IS_XUANXUAN_VER_
const char* file_prefix = "xuanxuan_";
#else
const char* file_prefix = "zenshot_";
#endif // IS_XUANXUAN_VER_

Workspace::Workspace(QWidget *host)
    : m_shotArea(this)
    , m_widget(host)
    , m_tool(nullptr)
    , m_hoverTool(new HoverTool(this))
    , m_textAssist(new TextAssist(this))
    , m_firstRender(false)
    , m_selectedShape(nullptr)
{
}

Workspace::~Workspace()
{
	L_FUNCTION();

    qDeleteAll(m_activeHandles);
    m_activeHandles.clear();

    m_shapeList.clear();

}

QWidget* Workspace::widget()
{
    return m_widget.get();
}

TextAssist *Workspace::textAssist() const
{
    return m_textAssist.get();
}

QRect Workspace::limitBoundary()
{
    return m_shotArea.allBoundary();
}

QPixmap Workspace::pixmap()
{
    return m_shotArea.allPixmap();
}

QRect Workspace::areaBoundary()
{
    return m_shotArea.areaBoundary();
}

void Workspace::setAreaBoundary(QRect rect)
{
    m_shotArea.setBoundary(rect);
}

void Workspace::start(std::shared_ptr<ScreenList> list, int index)
{
    L_FUNCTION();
    m_tool.reset(new AreaCreateTool(this));

    m_shotArea.start(list, index);

    L_TRACE("list->scale() = {0}, m_widget isvisable: {1}", list->scale(), m_widget->isVisible() ? 1 : 0);
    GParams::instance()->setScale(list->scale());
}

void Workspace::cleanup()
{
    L_FUNCTION();

    removeShape(m_selectedShape);
	m_selectedShape = nullptr;

    UserOper::cleanAll();
	
    if (m_toolBar != nullptr) {
		m_toolBar->move(0, -1000);
		m_toolBar->show();
		m_toolBar->setVisible(false);

        m_toolBar->cleanup();
    }
    
	qDeleteAll(m_activeHandles);
	m_activeHandles.clear();

	m_shapeList.clear();
    
    m_shotArea.cleanup();

    if (m_tool) m_tool->cleanup();
    if (m_createTool) m_createTool->cleanup();
    if (m_hoverTool) m_hoverTool->cleanup();

    m_propsBar = nullptr;
    m_createTool = nullptr;
    m_tool = nullptr;

    m_textAssist->cleanup();

    widget()->update();
}

void Workspace::onMousePress(QMouseEvent *event)
{
    QPoint mousePoint = getMouse(event);

    //截图区域未确定前，不执行其他鼠标操作
    if(m_shotArea.areaConfirmed() == true)
    {
        QRectF workArea = m_shotArea.areaBoundary();

        m_hoverTool->refresh(mousePoint);

        Handle *handle = m_hoverTool->shapeHandle();
        Handle *areaHandle = m_hoverTool->shotAeaHandle();
        std::shared_ptr<Shape> shape = m_hoverTool->shape();
        bool isSelf = m_hoverTool->shotAreaSelf();

        //鼠标单击，取消之前文本输入控件的绑定
        if(m_textAssist->editing()==true)
        {
            m_textAssist->unAttach();

            if(handle == nullptr &&
                    shape == nullptr &&
                    areaHandle == nullptr &&
                    m_createTool != nullptr &&
                    m_createTool->forType() == Utils::forTextKey())
            {
                setSelected(nullptr);
                m_tool = nullptr;
                m_lastMosue = mousePoint;

                return;
            }
        }

        if(handle != nullptr)
        {
            m_tool.reset(new HandleTool(this,handle));
        }
        else if(areaHandle != nullptr)
        {
            m_tool.reset(new AreaHandleTool(this,areaHandle));
        }
        else if(shape != nullptr)
        {
            //第二次单击到同一个文本图形，触发在位编辑功能
            if(m_selectedShape == shape && shape->type() == Utils::forTextKey())
            {
                Text* text = dynamic_cast<Text*>(shape.get());
                std::shared_ptr<Text> text_ptr(text);
                m_textAssist->attach(text_ptr);

                m_tool = nullptr;
            }
            else
            {
                if(shape != m_selectedShape){
                    setSelected(shape);
                }

                m_tool.reset(new MoveTool(this,shape));
            }
        }
        else if(isSelf == true && hasCreateTool() == false)
        {
            AreaMoveTool *areaMoveTool = new AreaMoveTool(this);
            m_tool.reset(areaMoveTool);
        }
        else if(m_createTool != nullptr)
        {
            if(workArea.contains(mousePoint) == false)
            {
                //不容许在截图区域之外创建图形
                m_tool = nullptr;
            }
            else
            {
                setSelected(nullptr);
                m_tool = m_createTool;
            }
        }
    }

    if(m_tool != nullptr) m_tool->onMousePress(mousePoint);

    m_lastMosue = mousePoint;
}

void Workspace::onMouseMove(QMouseEvent* event)
{
    //if(m_textAssist->editing() == true)
    //    return;

    QPoint mousePoint = getMouse(event);

    QPoint mouseOffset(mousePoint.x() - m_lastMosue.x(), mousePoint.y() - m_lastMosue.y());

    L_TRACE("m_tool = {0}", m_tool != nullptr ? "++++++++++++++" : "----------------");
    if(m_tool != nullptr) m_tool->onMouseMove(mousePoint,mouseOffset);

    m_lastMosue = mousePoint;
}

void Workspace::onMouseRelease(QMouseEvent *event)
{
    L_FUNCTION();

    QPoint mousePoint = getMouse(event);
    if(m_tool != nullptr)
    {
        m_tool->onMouseRelease(mousePoint);
    }

    m_tool = m_hoverTool;
}

void Workspace::onKeyPress(QKeyEvent *event)
{
    int key = event->key();
    switch( key )
    {
    case Qt::Key_Escape :
        close();
        break;
    case Qt::Key_Delete:
        deleteSelected();
    default:
        break;
    }
}

void Workspace::autoCapture()
{
    m_shotArea.autoCapture();
}

void Workspace::moveArea(QPoint offsetPoint)
{
   m_shotArea.move(offsetPoint);
}

void Workspace::confirmArea()
{
    L_FUNCTION();
    m_tool = nullptr;
    m_shotArea.confirmArea();
    m_widget->update();

    if(GParams::instance()->mark() == "yes")
    {
        //编辑模式构造工具栏
        createToolBar();
    }
    else
    {
        //非编辑模式直接保存截图并退出程序
        int result = saveImpl();
        closeImpl(result);
    }

    emit finishConfirmArea();
}

bool Workspace::areaConfirmed()
{
    return m_shotArea.areaConfirmed();
}

void Workspace::refreshDraw()
{
    m_widget->update();
}

void Workspace::draw(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing,true);

    m_shotArea.draw(painter);

    painter.setClipRect(areaBoundary());

    foreach(auto shape, m_shapeList)
    {
        if(shape == m_selectedShape &&
           m_selectedShape->type() == Utils::forTextKey() &&
           m_textAssist->editing() == true){
            continue;
        }
        shape->draw(painter);
    }

    foreach(Handle *handle, m_activeHandles)
    {
        handle->draw(painter);
    }

    if(m_firstRender == false && GParams::instance()->mark() == "yes")
    {
        L_DEBUG("create tool bar");

        m_firstRender = true;

        loadResource();
        m_toolBar.reset(new ToolBar(this));
        m_toolBar->move(0,-43200);
        m_toolBar->show();
        m_toolBar->setVisible(false);
    }
}

int Workspace::shapeCount()
{
    return m_shapeList.count();
}

Handle *Workspace::getShapeHandleAt(QPoint point)
{
    for(Handle* hdle:m_activeHandles)
    {
        if(hdle->contain(point) == true)
            return  hdle;
    }

    return nullptr;
}

std::shared_ptr<Shape> Workspace::getShapeAt(QPoint point)
{
    for(auto shape:m_shapeList)
    {
        if(shape->contain(point))
            return  shape;
    }

    return  nullptr;
}

Handle *Workspace::getShotAreaHandleAt(QPoint point)
{
    return  m_shotArea.handleAt(point);
}

bool Workspace::isShotAreaSelfAt(QPoint point)
{
    if(m_shapeList.count() > 0)
        return false;

    return m_shotArea.contain(point);
}

void Workspace::addShape(std::shared_ptr<Shape> shape)
{
    std::shared_ptr<Shape> ptr(shape);
    m_shapeList.append(ptr);
}

void Workspace::addMosaic(std::shared_ptr<Shape> shape)
{
    int newIndex = 0;
    for(int i=m_shapeList.size()-1;i>=0;i--)
    {
        if(m_shapeList[i]->type() == Utils::forMosaicKey())
        {
            newIndex = i+1;
            break;
        }
    }

    std::shared_ptr<Shape> ptr(shape);
    m_shapeList.insert(newIndex, ptr);
}

void Workspace::removeShape(std::shared_ptr<Shape> shape,bool tempOper)
{
    auto iter = std::find_if(m_shapeList.begin(), m_shapeList.end(), [=](std::shared_ptr<Shape> ptr)
        {
            return ptr == shape;
        });
    if (iter == m_shapeList.end())
    {
        return;
    }

    if (!tempOper && m_selectedShape == shape) 
    {
        setSelected(nullptr);
    }
    m_shapeList.erase(iter);
}

void Workspace::refreshProps()
{
//    if(m_textAssist->editing() == true)
//    {
//        m_textAssist->unAttach();
//    }
    if(m_selectedShape == nullptr)
    {
        L_DEBUG("{0} @ {1}: NO Selected Shape", __FUNCTION__, __LINE__);
        return;
    }

    L_DEBUG("{0} @ {1}: HAS Selected Shape", __FUNCTION__, __LINE__);

	MemoryStore oldStore;
	m_selectedShape->saveProps(&oldStore);

	m_selectedShape->loadProps();
	refreshDraw();

	MemoryStore nowStore;
	m_selectedShape->saveProps(&nowStore);

	std::shared_ptr<PropsCommand> propsComm(new PropsCommand(this, m_selectedShape.get(), oldStore, nowStore));
	UserOper::add(propsComm);

	if (m_selectedShape->type() == Utils::forTextKey() && m_textAssist->editing() == true)
	{
		m_textAssist->refreshProps();
	}
}

bool Workspace::hasCreateTool()
{
    return m_createTool == nullptr ? false : true;
}

void Workspace::setSelected(std::shared_ptr<Shape> newSelected)
{
    L_FUNCTION();
    if(m_selectedShape == newSelected)
        return;

    //之前的图形设置成未选中状态
    if(m_selectedShape != nullptr)
    {
        L_DEBUG("m_selectedShape->setSelected(false)");
        m_selectedShape->setSelected(false);
    }

    L_DEBUG("m_activeHandles.clear()");
    //删除控制手柄并重置选中的图形
    m_activeHandles.clear();
    m_selectedShape = newSelected;

    //设置新图形的选中状态，并获取对应的控制手柄
    if(m_selectedShape != nullptr)
    {
        L_DEBUG("m_selectedShape->setSelected(true)");
        m_selectedShape->setSelected(true);
        m_activeHandles = m_selectedShape->handles();
    }

    //重置创建工具，及其面板上图形创建工具的激活状态
    if(m_selectedShape != nullptr && m_toolBar != nullptr)
    {
        L_DEBUG("m_selectedShape->saveProps()");
        m_selectedShape->saveProps();
        m_toolBar->highlightCreateBtn(m_selectedShape->type());
        m_createTool.reset(createCreateToolFactory(m_selectedShape->type()));
        m_createTool->cleanup();
    }

    refreshDraw();
    createPropsBar();
}

const QVector<Handle *>& Workspace::activeHandles() const
{
    return m_activeHandles;
}

void Workspace::normalbeforeUndo()
{
    if(m_selectedShape != nullptr &&
       m_selectedShape->type() == Utils::forTextKey() &&
       m_textAssist->editing() == true)
    {
        m_textAssist->unAttach();
    }
}

void Workspace::deleteSelected()
{
    if(m_selectedShape == nullptr)
    {
        return;
    }

    if(m_selectedShape->type() == Utils::forTextKey() && m_textAssist->editing() == true)
    {
        m_textAssist->unAttach();
    }

    std::shared_ptr<DeleteCommand> delComm(new DeleteCommand(this,m_selectedShape));
    UserOper::add(delComm);

    removeShape(m_selectedShape);
    setSelected(nullptr);
}

void Workspace::createToolBar()
{
    L_FUNCTION();
    //loadResource();
    //m_toolBar = new ToolBar(this);
    //m_toolBar->show();

    m_toolBar->setVisible(true);

    connect(m_toolBar.get(), SIGNAL(createChanged(QString)), this, SLOT(createToolChanged(QString)));
    connect(m_toolBar.get(),SIGNAL(download()),this,SLOT(download()));
    connect(m_toolBar.get(),SIGNAL(closeProgram()),this,SLOT(close()));
    connect(m_toolBar.get(),SIGNAL(save()),this,SLOT(save()));
    rePositionBar();
}

void Workspace::createPropsBar()
{
    L_FUNCTION();
    QString shapeType = "";

    if(m_selectedShape != nullptr)
        shapeType = m_selectedShape->type();
    else if(m_createTool != nullptr)
        shapeType = m_createTool->forType();

    m_propsBar.reset(createPropsBarFactory(shapeType));
    m_propsBar->show();

    rePositionBar();
}

Tool *Workspace::createTool() const
{
    return m_createTool ? m_createTool.get() : nullptr;
}

void Workspace::rePositionBar()
{
    if(m_toolBar == nullptr)
        return;

    int rowGap = 0;

    QRectF screenRect = m_shotArea.allBoundary();
    QRectF shotRect = m_shotArea.areaBoundary();

    int toolWidth = m_toolBar->width();
    int toolHeight = m_toolBar->height();

    int propsWidth = 0;
    int propsHeight = 0;
    if(m_propsBar != nullptr)
    {
        rowGap = Utils::ToolBar_PropsBar_Gap;

        propsWidth = m_propsBar->width();
        propsHeight = m_propsBar->height();
    }

    int totalWidth = qMax(toolWidth,propsWidth);
    int totalHeight = toolHeight + rowGap + propsHeight;

    //计算纵坐标的值,默认紧贴当前屏幕的底部
    int y = screenRect.y();

    if(shotRect.y()+shotRect.height()+Utils::ToolBar_ShotArea_Gap + totalHeight <= screenRect.y()+screenRect.height())
    {
        //优先在截图区域的右下角显示
        y = shotRect.y() + shotRect.height() + Utils::ToolBar_ShotArea_Gap;
    }
    else if(shotRect.y() - Utils::ToolBar_ShotArea_Gap - totalHeight >= screenRect.y())
    {
        //其次在截图区域的右上角显示
        y = shotRect.y() - Utils::ToolBar_ShotArea_Gap - totalHeight;
    }

    //计算横坐标的值（优先右侧显示）
    int x = shotRect.x() + shotRect.width() - totalWidth;
    if(x >= screenRect.x())
    {
        m_toolBar->move(x + (totalWidth - toolWidth), y);

        if(m_propsBar != nullptr)
        {
            m_propsBar->move(x,y+toolHeight+rowGap);
        }
    }
    else
    {
        //左侧显示
        x = shotRect.x();

        m_toolBar->move(x, y);

        if(m_propsBar != nullptr)
        {
            m_propsBar->move(x,y+toolHeight+rowGap);
        }
    }
}

void Workspace::createToolChanged(QString shapeType)
{
    L_FUNCTION();
    if (m_createTool)
    {
        m_createTool->cleanup();
    }
    m_createTool.reset(createCreateToolFactory(shapeType));

    setSelected(nullptr);
    createPropsBar();
}

void Workspace::download()
{
    L_INFO("############################### down load slot");
    QPixmap result = m_shotArea.result();

    LocalStore store;

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyyMMdd_hhmmss");
    QString savefile=file_prefix+current_date+".png";
    QString savepath=store.read("Setting","QuickSaveDir",".").toString();

    QString fileName = QFileDialog::getSaveFileName(widget(),QObject::tr("save file"),savepath+"/"+savefile,"PNG File (*.png)");
    if (!fileName.isEmpty())
    {
        result.toImage().save(fileName, "png");

        QFileInfo fileInfo(fileName);
        QString folder = fileInfo.path();
        store.write("Setting", "QuickSaveDir", folder);
    }

    close();
}

int Workspace::saveClipboardImpl()
{
    QPixmap result = m_shotArea.result();
    QClipboard *board = QApplication::clipboard();
    board->setImage(result.toImage());

    return 0;
}

int Workspace::saveFolderImpl(QString folderPath)
{
    QDir dir(folderPath);
    if(dir.exists() == false)
    {
        return saveClipboardImpl();
    }
    else
    {
        QPixmap result = m_shotArea.result();

        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyyMMdd_hhmmss");
        QString fileName =file_prefix+current_date+".png";
        QString savefile = dir.filePath(fileName);

        result.toImage().save(savefile,"png");

        return 0;
    }
}

int Workspace::saveImpl()
{
    bool toFile = false;
    bool toClipboard = false;

    //判断是否保存为指定的文件
    if(GParams::instance()->save() != nullptr)
    {
        QFile file(GParams::instance()->save());
        QFileInfo fInfo(file);
        QDir dir = fInfo.dir();

        QString suffix = fInfo.suffix().toLower();

        //文件格式错误，异常退出
        if(suffix != "png")
            return Utils::ERROR_SAVE_FORMAT;

        //指定文件夹不存在，异常退出
        if(dir.exists() == false)
            return Utils::ERROR_SAVE_FOLDER;

        //如文件已存在，先删除
        if(file.exists() == true)
            file.remove();

        toFile = true;
    }

    //判断是否保存到剪贴板
    if(GParams::instance()->clipboard() == "yes")
    {
        toClipboard = true;
    }
    else if(GParams::instance()->clipboard() == "auto")
    {
        if(toFile == false)
            toClipboard = true;
    }

    if(toClipboard == true)
        saveClipboardImpl();

    if(toFile == true)
    {
        QPixmap result = m_shotArea.result();
        result.toImage().save(GParams::instance()->save(),"png");
    }

    return 0;
}

void Workspace::save()
{
    int result = saveImpl();
    closeImpl(result);
}

Tool *Workspace::createCreateToolFactory(QString shapeType)
{
    Tool *tool = nullptr;

    if(shapeType == Utils::forRectKey())
        tool = new RectCreateTool(this);
    else if(shapeType == Utils::forLineKey())
        tool = new LineCreateTool(this);
    else if(shapeType == Utils::forEllipseKey())
        tool = new EllipseCreateTool(this);
    else if(shapeType == Utils::forArrowKey())
        tool = new ArrowCreateTool(this);
    else if(shapeType == Utils::forCurveKey())
        tool = new CurveCreateTool(this);
    else if(shapeType == Utils::forTextKey())
        tool = new TextCreateTool(this);
    else if(shapeType == Utils::forMosaicKey())
        tool = new MosaicCreateTool(this);

    return tool;
}

PropsBar *Workspace::createPropsBarFactory(QString shapeType)
{
    PropsBar *propsBar = nullptr;

    if(shapeType == Utils::forArrowKey())
        propsBar = new ArrowBar(this);
    else if(shapeType == Utils::forCurveKey())
        propsBar = new CurveBar(this);
    else if(shapeType == Utils::forEllipseKey())
        propsBar = new EllipseBar(this);
    else if(shapeType == Utils::forLineKey())
        propsBar = new LineBar(this);
    else if(shapeType == Utils::forMosaicKey())
        propsBar = new MosaicBar(this);
    else if(shapeType == Utils::forRectKey())
        propsBar = new RectangleBar(this);
    else if(shapeType == Utils::forTextKey())
        propsBar = new TextBar(this);

    return propsBar;
}

void Workspace::closeImpl(int code)
{
    L_FUNCTION();
    emit quitShot(code);

	disconnect(m_toolBar.get(), SIGNAL(createChanged(QString)), this, SLOT(createToolChanged(QString)));
    disconnect(m_toolBar.get(), SIGNAL(download()), this, SLOT(download()));
    disconnect(m_toolBar.get(), SIGNAL(closeProgram()), this, SLOT(close()));
    disconnect(m_toolBar.get(), SIGNAL(save()), this, SLOT(save()));
}

void Workspace::close()
{
    L_FUNCTION();
    closeImpl(0);
}

QPoint Workspace::getMouse(QMouseEvent *event)
{
    return QPoint(event->x(), event->y());
}

void Workspace::loadResource()
{
    //加载样式文件
    QString qssFile = ":/style.css";
    QFile file(qssFile);

    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    file.close();


    if(GParams::instance()->scale() != 1.0)
    {
        GScale scale;

        QRegExp rx("\\d+px", Qt::CaseInsensitive);
        rx.setMinimal(true);
        int index = -1;

        while ((index = rx.indexIn(qss, index + 1)) >= 0)
        {
            int capLen = rx.cap(0).length() - 2;
            QString snum = qss.mid(index, capLen);
            snum = QString::number(scale.ts(snum.toInt()));
            qss.replace(index, capLen, snum);
            index += snum.length();
            if (index > qss.size() - 2)
            {
                break;
            }
        }
    }

    m_widget->setStyleSheet(qss);
}
