#include "setting/settingdlg.h"

#include "config/xmlconfig.h"
#include "spdlogwrapper.hpp"

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <QFile>
#include <QVariant>

#ifdef _WINDOWS
#include <Windows.h>
#include <WinUser.h>
#endif // _WINDOWS


#define SETTING_XML_NAME "./setting.xml"

SettingDlg::SettingDlg(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , m_KeyValue(0)
    , m_EnableHotKey(0)
    , m_HotKeyStat(0)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() | Qt::Tool);

    memset(m_SetKeyValue, 0, sizeof(m_SetKeyValue));

    qRegisterMetaType<int32_t>("int32_t");
    qRegisterMetaType<uint32_t>("uint32_t");

    initDlg();
    initStat();
    setupSingal();
}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::closeEvent(QCloseEvent* event)
{
    (void*)event;
    hide();
}

void SettingDlg::initDlg()
{
    // load qss
    QString qssFile = ":/setting.css";
    QFile file(qssFile);

    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    file.close();

    setStyleSheet(qss);
    
    // modif style
    setWindowTitle(tr("setting_title"));

    m_EnableHotKey = findChild<QCheckBox*>("checkHotKey");
    m_EnableHotKey->setText(tr("hotkey_title"));

    QPushButton* hotkey_value = findChild<QPushButton*>("hotkeyValue");
    hotkey_value->setText(tr("hotkey_default"));

    m_HotKeyStat = findChild<QPushButton*>("hotkeyStatus");
    m_HotKeyStat->setText(tr("hotkey_stat_normal"));
    m_HotKeyStat->setProperty("class", "setting-check");
    m_HotKeyStat->setCheckable(true);

    QPushButton* save = findChild<QPushButton*>("settingSaveBtn");
    save->setText(tr("hotkey_save"));

    QPushButton* cancel = findChild<QPushButton*>("settingCancelBtn");
    cancel->setText(tr("hotkey_cancel"));
}

void SettingDlg::initStat()
{
    GetXMLConfig().LoadConfig(SETTING_XML_NAME);
    int32_t stat = static_cast<int32_t>(GetXMLConfig().GetConfigNum2("config", "enable"));
    uint32_t value = static_cast<uint32_t>(GetXMLConfig().GetConfigNum2("config", "hotkey"));
    m_EnableHotKey->setChecked(stat != 0);
    
    emit UpdateHotKeyText(value);
}

void SettingDlg::setupSingal()
{
    connect(m_EnableHotKey, SIGNAL(stateChanged(int)), this, SLOT(OnUseHotKeyChecked(int)));
    connect(this, SIGNAL(UpdateHotKeyText(uint32_t)), this, SLOT(OnUpdateHotKeyText(uint32_t)));
    connect(this, SIGNAL(UpdateHotKeyValue(uint32_t)), this, SLOT(OnUpdateHotKeyValue(uint32_t)));
    connect(this, SIGNAL(UpdateHotKeyResult(bool)), this, SLOT(OnUpdateHotKeyResult(bool)));

    QPushButton* save = findChild<QPushButton*>("settingSaveBtn");
    connect(save, SIGNAL(clicked()), this, SLOT(OnSaveHotKeyConfig()));

    QPushButton* cancel = findChild<QPushButton*>("settingCancelBtn");
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}

QString SettingDlg::getHotKeyStr(uint32_t value)
{
    if (!value) {
        return tr("hotkey_default");
    }

    std::string vk_str;
    char key_text[0x10] = { 0 };
    uint8_t key0, key1, key2;
    key0 = ((value >> 16) & 0x000000FF);
    key1 = ((value >> 8) & 0x000000FF);
    key2 = (value & 0x000000FF);
    if (key0 && GetKeyNameTextA(MapVirtualKey(key0, MAPVK_VK_TO_VSC) << 16, key_text, sizeof(key_text) / sizeof(key_text[0]) - 1)) {
        vk_str.append(key_text).append("+");
    }
    if (key1 && GetKeyNameTextA(MapVirtualKey(key1, MAPVK_VK_TO_VSC) << 16, key_text, sizeof(key_text) / sizeof(key_text[0]) - 1)) {
        vk_str.append(key_text).append("+");
    }
    if (key2 && GetKeyNameTextA(MapVirtualKey(key2, MAPVK_VK_TO_VSC) << 16, key_text, sizeof(key_text) / sizeof(key_text[0]) - 1)) {
        vk_str.append(key_text).append("+");
    }
    if (!vk_str.empty()) {
        vk_str.pop_back();
    }

    return vk_str.c_str();
}

void SettingDlg::OnUseHotKeyChecked(int stat)
{
    QPushButton* hotkey_value = findChild<QPushButton*>("hotkeyValue");
    hotkey_value->setEnabled(stat == Qt::Checked);

    if (stat == Qt::Checked) {
        hotkey_value->setText(tr("reset_hotkey"));
        memset(m_SetKeyValue, 0, sizeof(m_SetKeyValue));
    }
    else {
        int current_vk[3] = { 0 };
        if (!current_vk[0]) {
            hotkey_value->setText(tr("hotkey_default"));
        }
        else {
            QString vk;
            hotkey_value->setText(vk);
        }
    }
}

void SettingDlg::OnUpdateHotKeyText(uint32_t value)
{
    QPushButton* hotkey_value = findChild<QPushButton*>("hotkeyValue");
    hotkey_value->setEnabled(stat != 0);
    QString vk_str = getHotKeyStr(value);

    hotkey_value->setText(vk_str);
}

void SettingDlg::OnUpdateHotKeyValue(uint32_t value)
{
    if (m_KeyValue && m_KeyValue == value) {
        return;
    }
    if (m_KeyValue) {
        UnregisterHotKey(reinterpret_cast<HWND>(parentWidget()->winId()), m_KeyValue);
    }

    UINT fsModifiers, vk;
    fsModifiers = vk = 0;
    uint8_t key0, key1, key2;
    key0 = ((value >> 16) & 0x000000FF);
    key1 = ((value >> 8) & 0x000000FF);
    key2 = (value & 0x000000FF);

    if (key0 == VK_CONTROL || key1 == VK_CONTROL || key2 == VK_CONTROL) {
        fsModifiers |= MOD_CONTROL;
    }
    if (key0 == VK_SHIFT || key1 == VK_SHIFT || key2 == VK_SHIFT) {
        fsModifiers |= MOD_SHIFT;
    }
    if ((key0 == VK_LWIN || key1 == VK_LWIN || key2 == VK_LWIN) || (key0 == VK_RWIN || key1 == VK_RWIN || key2 == VK_RWIN) ){
        fsModifiers |= MOD_WIN;
    }
    if (key0 == VK_MENU || key1 == VK_MENU || key2 == VK_MENU) {
        fsModifiers |= MOD_ALT;
    }
    if (key0 >= 0x30 && key0 <= 0x5A) {
        vk = key0;
    } else if (key1 >= 0x30 && key1 <= 0x5A) {
        vk = key1;
    } else if (key2 >= 0x30 && key2 <= 0x5A) {
        vk = key2;
    }
    if (!fsModifiers && !vk) {
        return;
    }

    BOOL result = RegisterHotKey(reinterpret_cast<HWND>(parentWidget()->winId()), value, fsModifiers, vk);

    emit UpdateHotKeyResult(result ? true : false);
    
    if (result) {
        m_KeyValue = value;
    }

    OnSaveHotKeyConfig();
}

void SettingDlg::OnUpdateHotKeyResult(bool success)
{
    m_HotKeyStat->setChecked(!success);
}

void SettingDlg::OnSaveHotKeyConfig()
{
    GetXMLConfig().SetConfigNum2("config", "enable", m_EnableHotKey->isChecked() ? 1 : 0);
    GetXMLConfig().SetConfigNum2("config", "hotkey", m_KeyValue);
    GetXMLConfig().SaveConfig(SETTING_XML_NAME);
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool SettingDlg::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
#else
bool SettingDlg::nativeEvent(const QByteArray& eventType, void* message, long* result)
#endif
{
    if (!m_EnableHotKey->isChecked()) {
        return QWidget::nativeEvent(eventType, message, result);
    }
#ifdef _WINDOWS
    MSG* msg = static_cast<MSG*>(message);
    uint8_t key = 0;
    uint8_t key_msg = 0;
    switch (msg->message) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        key_msg = 1;
        key = static_cast<uint8_t>(msg->wParam);
        break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        key_msg = 2;
        key = static_cast<uint8_t>(msg->wParam);
        break;
    }

    if (key_msg == 1) {
        for (int i = 0; key && i < sizeof(m_SetKeyValue) / sizeof(m_SetKeyValue[0]); i++) {
            if (m_SetKeyValue[i] == key) {
                return QWidget::nativeEvent(eventType, message, result);
            }
        }

        for (int i = 0; key && i < sizeof(m_SetKeyValue) / sizeof(m_SetKeyValue[0]); i++) {
            if (!m_SetKeyValue[i]) {
                m_SetKeyValue[i] = key;

                uint32_t value = ((m_SetKeyValue[0] << 16) & 0x00FF0000) | ((m_SetKeyValue[1] << 8) & 0x0000FF00) | (m_SetKeyValue[2] & 0x000000FF);
                emit UpdateHotKeyText(value);
                break;
            }
        }
    }
    else if (key_msg == 2) {
        for (int i = 0; i < sizeof(m_SetKeyValue) / sizeof(m_SetKeyValue[0]); i++) {
            if (m_SetKeyValue[i] && (GetKeyState(m_SetKeyValue[i]) & 0x8000)) {
                return QWidget::nativeEvent(eventType, message, result);
            }
        }

        uint32_t value = ((m_SetKeyValue[0] << 16) & 0x00FF0000) | ((m_SetKeyValue[1] << 8) & 0x0000FF00) | (m_SetKeyValue[2] & 0x000000FF);
        emit UpdateHotKeyValue(value);
        emit UpdateHotKeyText(value);
    }
#endif // _WINDOWS

    return QWidget::nativeEvent(eventType, message, result);
}
