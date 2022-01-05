#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QHBoxLayout>
#include <QButtonGroup>

#include "core/gscale.h"

class Workspace;

/**
 * @class : ToolBar
 * @brief : 主工具栏定义
 * @note  : 提供常用功能的选择，切换
 */
class ToolBar : public QWidget,GScale
{
    Q_OBJECT
public:
    explicit ToolBar(Workspace *workspace);

    void createChild();
    void highlightCreateBtn(QString shapeType);

private:
    QHBoxLayout *m_layout;
    QButtonGroup *btnGroup;

    Workspace *m_workspace;
    QVector<QString> m_createBtnKeyList;

    QPushButton *m_undoBtn;
    QPushButton *m_redoBtn;

    void createCreateButtons();
    void createFunctionButons();

    void createSingleCreateButton(QButtonGroup *group,QString shapeType,QString iconStr,QString tipStr);
    QPushButton *createSingleFunctionButton(QString iconStr,QString tipStr,QString objectName=NULL);

    void addSeperator();

signals:
    void createChanged(QString shapeType);
    void save();
    void download();
    void closeProgram();

private slots:
    void undo();
    void redo();
    void operChanged();
    void createBtnClicked(int index);
    void downloadBtnClicked();
    void saveBtnClicked();
    void closeProgramBtnClicked();
};

#endif // TOOLBAR_H
