/* Copyright (C) 2021 Nature Easy Soft Network Technology Co., LTD
 *
 * This file is part of Zenshot (https://github.com/easysoft/zenshot/).
 *
 * Zenshot is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zenshot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zenshot. If not, see <https://www.gnu.org/licenses/>.
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
