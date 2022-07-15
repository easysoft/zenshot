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
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#else
    virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif

private:
    void initDlg();
    void initStat();
    void setupSingal();
    QString getHotKeyStr(uint32_t value);

signals:
    void UpdateHotKeyText(uint32_t value);
    void UpdateHotKeyValue(uint32_t value);
    void UpdateHotKeyResult(bool success);

private slots:
    void OnUseHotKeyChecked(int stat);
    void OnUpdateHotKeyText(uint32_t value);        // 更新热键显示
    void OnUpdateHotKeyValue(uint32_t value);       // 注册热键
    void OnUpdateHotKeyResult(bool success);        // 热键注册结果
    void OnSaveHotKeyConfig();

private:
    Ui::SettingDlg ui;
    uint32_t m_KeyValue;
    uint32_t m_SetKeyValue[3];
    QCheckBox* m_EnableHotKey;
    QPushButton* m_HotKeyStat;
    QPushButton* m_HotKeyValue;
}; // SettingDlg

#endif // SETTINGDLG_H
