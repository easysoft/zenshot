#include "mosaiccreatetool.h"
#include "screen/workspace.h"
#include "core/useroper.h"
#include "commands/addcommand.h"

MosaicCreateTool::MosaicCreateTool(Workspace *workspace) : Tool(workspace)
{

}

QString MosaicCreateTool::forType()
{
    return Utils::forMosaicKey();
}

void MosaicCreateTool::setCursor()
{
    QPixmap pixmap(":/images/mosaic.png");
    QSize pixsize(18,18);
    QPixmap scaledPixmap = pixmap.scaled(pixsize,Qt::KeepAspectRatio);
    QCursor cursor(scaledPixmap,-1,-1);

    m_workspace->widget()->setCursor(cursor);
}

void MosaicCreateTool::onMousePress(QPoint mousePoint)
{
    m_shape = new Mosaic(m_workspace);

    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));

    m_workspace->addMosaic(m_shape);
}

void MosaicCreateTool::onMouseMove(QPoint mousePoint, QPoint mouseOffset)
{
    m_shape->addPoint(QPoint(mousePoint.x(),mousePoint.y()));
    m_workspace->refreshDraw();
}

void MosaicCreateTool::onMouseRelease(QPoint mousePoint)
{
    m_workspace->refreshDraw();

    AddCommand *addComm = new AddCommand(m_workspace,m_shape);
    UserOper::add(addComm);
}

