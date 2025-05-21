/**
 * ZenShot - Open-source cross-platform screenshot tool.
 *
 * @copyright Copyright 2009-2025 禅道软件（青岛）有限公司(ZenTao Software (Qingdao) Co., Ltd. www.chandao.com)
 * @license   LGPL v3.0 - Full terms in LICENSE file.
 * @notice    This program uses Qt which is licensed under LGPL v3.
 */

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
    virtual ~ToolBar();

    void createChild();
    void highlightCreateBtn(QString shapeType);
    void cleanup();

private:
    QHBoxLayout m_layout;
    QButtonGroup btnGroup;

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
    void ShowPreview(Workspace* w);

private slots:
    void undo();
    void redo();
    void operChanged();
    void createBtnClicked(int index);
    void downloadBtnClicked();
    void saveBtnClicked();
    void closeProgramBtnClicked();
#if !NZENTAO_VER_
    void OnShowPreviewClicked();
#endif // NZENTAO_VER_
};

#endif // TOOLBAR_H
