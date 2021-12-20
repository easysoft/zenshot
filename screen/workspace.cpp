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

#include "core/useroper.h"
#include "commands/deletecommand.h"
#include "commands/propscommand.h"
#include "stores/memorystore.h"
#include "core/appparams.h"

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


Workspace::Workspace(QWidget *host):m_shotArea(this)
{
    m_selectedShape = nullptr;

    this->m_widget = host;
    this->m_tool = new AreaCreateTool(this);
    this->m_hoverTool = new HoverTool(this);

    this->m_createTool = nullptr;
    this->m_toolBar = nullptr;
    this->m_propsBar = nullptr;

    m_textAssist = new TextAssist(this);
}

Workspace::~Workspace()
{
    if(m_tool != nullptr)
    {
        delete m_tool;
        m_tool = nullptr;
    }

    delete m_hoverTool;
    m_hoverTool = nullptr;

    if(m_createTool != nullptr)
    {
        delete m_createTool;
        m_createTool = nullptr;
    }

    qDeleteAll(m_activeHandles);
    m_activeHandles.clear();

    qDeleteAll(m_shapeList);
    m_shapeList.clear();

}

QFont Workspace::iconfont() const
{
    return m_iconfont;
}

QWidget* Workspace::widget()
{
    return m_widget;
}

TextAssist *Workspace::textAssist() const
{
    return m_textAssist;
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

void Workspace::start(ScreenList *list)
{
    m_shotArea.start(list);
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
        Shape *shape = m_hoverTool->shape();
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
            m_tool = new HandleTool(this,handle);
        }
        else if(areaHandle != nullptr)
        {
            m_tool = new AreaHandleTool(this,areaHandle);
        }
        else if(shape != nullptr)
        {
            //第二次单击到同一个文本图形，触发在位编辑功能
            if(m_selectedShape == shape && shape->type() == Utils::forTextKey())
            {
                Text *text = dynamic_cast<Text*>(shape);
                m_textAssist->attach(text);

                m_tool = nullptr;
            }
            else
            {
                if(shape != m_selectedShape){
                    setSelected(shape);
                }

                m_tool = new MoveTool(this,shape);
            }
        }
        else if(isSelf == true && hasCreateTool() == false)
        {
            AreaMoveTool *areaMoveTool = new AreaMoveTool(this);
            m_tool = areaMoveTool;
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

void Workspace::onMouseMove(QMouseEvent *event)
{
    //if(m_textAssist->editing() == true)
    //    return;

    QPoint mousePoint = getMouse(event);

    QPoint mouseOffset(mousePoint.x()-m_lastMosue.x(), mousePoint.y()-m_lastMosue.y());

    if(m_tool != nullptr) m_tool->onMouseMove(mousePoint,mouseOffset);

    m_lastMosue = mousePoint;
}

void Workspace::onMouseRelease(QMouseEvent *event)
{
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
    m_tool = nullptr;
    m_shotArea.confirmArea();
    m_widget->update();

    if(AppParams::instance()->mode() == "view")
    {
        //非编辑模式直接保存截图并退出程序
        if(AppParams::instance()->save() == "clipboard")
        {
            saveToClipboardImpl();
            close();
        }
        else
        {
            QString folder = AppParams::instance()->save();
            saveToFolder(folder);
            close();
        }
    }
    else
    {
        //编辑模式构造工具栏
        createToolBar();
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

    foreach(Shape *shape, m_shapeList)
    {
        shape->draw(painter);
    }

    foreach(Handle *handle, m_activeHandles)
    {
        handle->draw(painter);
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

Shape *Workspace::getShapeAt(QPoint point)
{
    for(Shape* shape:m_shapeList)
    {
        if(shape->contain(point) == true)
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

void Workspace::addShape(Shape *shape)
{
    m_shapeList.append(shape);
}

void Workspace::addMosaic(Shape *shape)
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

    m_shapeList.insert(newIndex,shape);
}

void Workspace::removeShape(Shape *shape,bool tempOper)
{
    if(m_shapeList.contains(shape))
    {
        m_shapeList.removeOne(shape);

        if(tempOper == false && m_selectedShape == shape)
        {
            setSelected(nullptr);
        }
    }
}

void Workspace::refreshProps()
{
//    if(m_textAssist->editing() == true)
//    {
//        m_textAssist->unAttach();
//    }

    if(m_selectedShape != nullptr)
    {
        MemoryStore oldStore;
        m_selectedShape->saveProps(&oldStore);

        m_selectedShape->loadProps();
        refreshDraw();

        MemoryStore nowStore;
        m_selectedShape->saveProps(&nowStore);

        PropsCommand *propsComm = new PropsCommand(this,m_selectedShape,oldStore,nowStore);
        UserOper::add(propsComm);

        if(m_selectedShape->type() == Utils::forTextKey() && m_textAssist->editing() == true)
        {
            m_textAssist->refreshProps();
        }
    }
}

bool Workspace::hasCreateTool()
{
    return m_createTool == nullptr ? false : true;
}

void Workspace::setSelected(Shape *newSelected)
{
    if(m_selectedShape == newSelected)
        return;

    //之前的图形设置成未选中状态
    if(m_selectedShape != nullptr)
    {
        m_selectedShape->setSelected(false);
    }

    //删除控制手柄并重置选中的图形
    m_activeHandles.clear();
    m_selectedShape = newSelected;

    //设置新图形的选中状态，并获取对应的控制手柄
    if(m_selectedShape != nullptr)
    {
        m_selectedShape->setSelected(true);
        m_activeHandles = m_selectedShape->handles();
    }

    //重置创建工具，及其面板上图形创建工具的激活状态
    if(m_selectedShape != nullptr && m_toolBar != nullptr)
    {
        m_selectedShape->saveProps();
        m_toolBar->highlightCreateBtn(m_selectedShape->type());
        m_createTool = createCreateToolFactory(m_selectedShape->type());
    }

    refreshDraw();
    createPropsBar();
}

QVector<Handle *> Workspace::activeHandles() const
{
    return m_activeHandles;
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

    DeleteCommand *delComm = new DeleteCommand(this,m_selectedShape);
    UserOper::add(delComm);

    removeShape(m_selectedShape);
    setSelected(nullptr);
}

void Workspace::createToolBar()
{
    loadResource();

    m_toolBar = new ToolBar(this);

    connect(m_toolBar,SIGNAL(createChanged(QString)),this,SLOT(createToolChanged(QString)));
    connect(m_toolBar,SIGNAL(saveToSelect()),this,SLOT(saveToSelect()));
    connect(m_toolBar,SIGNAL(closeProgram()),this,SLOT(close()));
    connect(m_toolBar,SIGNAL(saveToClipboard()),this,SLOT(saveToClipboard()));

    rePositionBar();
}

void Workspace::createPropsBar()
{
    if(m_propsBar != nullptr)
    {
        m_propsBar->deleteLater();
        m_propsBar = nullptr;
    }

    QString shapeType = "";

    if(m_selectedShape != nullptr)
        shapeType = m_selectedShape->type();
    else if(m_createTool != nullptr)
        shapeType = m_createTool->forType();

    m_propsBar = createPropsBarFactory(shapeType);

    if(m_propsBar != nullptr)
    {
        m_propsBar->show();
    }

    rePositionBar();
}

Tool *Workspace::createTool() const
{
    return m_createTool;
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

    //计算横坐标的值，优先右侧显示，其次紧靠左侧显示
    int x = shotRect.x() + shotRect.width() - totalWidth;
    if(x < screenRect.x())
    {
        x = screenRect.x();
    }

    //计算纵坐标的值
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

    //最后紧贴屏幕的顶部，截图区域的右侧显示

    m_toolBar->move(x, y);

    if(m_propsBar != nullptr)
    {
        m_propsBar->move(x,y+toolHeight+rowGap);
    }
}

void Workspace::createToolChanged(QString shapeType)
{
    m_createTool = createCreateToolFactory(shapeType);

    setSelected(nullptr);
    createPropsBar();
}

void Workspace::saveToSelect()
{
    QPixmap result = m_shotArea.result();

    LocalStore store;

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyyMMdd_hhmmss");
    QString savefile="xuanxuan_"+current_date+".png";
    QString savepath=store.read("Setting","QuickSaveDir",".").toString();

    QString fileName = QFileDialog::getSaveFileName(widget(),QObject::tr("save file"),savepath+"/"+savefile,"PNG File (*.png)");
    result.toImage().save(fileName,"png");

    QFileInfo fileInfo(fileName);
    QString folder = fileInfo.path();
    store.write("Setting","QuickSaveDir",folder);

    close();
}

void Workspace::saveToClipboardImpl()
{
    QPixmap result = m_shotArea.result();
    QClipboard *board = QApplication::clipboard();
    board->setImage(result.toImage());
}

void Workspace::saveToFolder(QString folderPath)
{
    QDir dir(folderPath);
    if(dir.exists() == false)
    {
        saveToClipboardImpl();
    }
    else
    {
        QPixmap result = m_shotArea.result();

        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyyMMdd_hhmmss");
        QString fileName ="xuanxuan_"+current_date+".png";
        QString savefile = dir.filePath(fileName);

        result.toImage().save(savefile,"png");
    }
}

void Workspace::saveToClipboard()
{
    if(AppParams::instance()->save() == "clipboard")
    {
        saveToClipboardImpl();
    }
    else
    {
        QString folder = AppParams::instance()->save();
        saveToFolder(folder);
    }

    close();
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

void Workspace::close()
{
    emit quitShot();
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
    m_widget->setStyleSheet(qss);
    file.close();

}


