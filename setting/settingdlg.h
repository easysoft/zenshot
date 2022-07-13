#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#include <QDialog>

#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

#include "ui_setting.h"

class SettingDlg : public QDialog {
    Q_OBJECT

    enum {
        BTN_ID_ZENTAO = 0,
        BTN_ID_SHORTKEY,
    };
public:
    explicit SettingDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~SettingDlg();

protected:
    void closeEvent(QCloseEvent*) override;

private:
    void initDlg();
    void initStat();
    void setupSingal();

private slots:
    void OnUseHotKeyChecked(int stat);
    void SaveHotKeyConfig();

private:
    Ui::SettingDlg ui;
}; // SettingDlg

#endif // SETTINGDLG_H
