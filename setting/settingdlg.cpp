#include "setting/settingdlg.h"

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <QFile>
#include <QVariant>

#define SETTING_XML_NAME "D:/setting.xml"

static int64_t GetXmlNumber(const rapidxml::xml_node<>* node, const char* node_key);
static std::string GetXmlString(const rapidxml::xml_node<>* node, const char* node_key);
static const char* GetVkString(int vk);

SettingDlg::SettingDlg(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{   
    ui.setupUi(this);
    setWindowFlags(windowFlags() | Qt::Tool);

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

    QCheckBox* hotkey_title = findChild<QCheckBox*>("checkHotKey");
    hotkey_title->setText(tr("hotkey_title"));

    QPushButton* hotkey_value = findChild<QPushButton*>("hotkeyValue");
    hotkey_value->setText(tr("hotkey_default"));

    QPushButton* hotkey_stat = findChild<QPushButton*>("hotkeyStatus");
    hotkey_stat->setText(tr("hotkey_stat_normal"));
    hotkey_stat->setProperty("class", "setting-check");
    hotkey_stat->setCheckable(true);

    QPushButton* save = findChild<QPushButton*>("settingSaveBtn");
    save->setText(tr("hotkey_save"));

    QPushButton* cancel = findChild<QPushButton*>("settingCancelBtn");
    cancel->setText(tr("hotkey_cancel"));
}

void SettingDlg::initStat()
{
    int stat = 0;
    int vk[3] = { 0 };
    try {
        rapidxml::file<> fdoc(SETTING_XML_NAME);
        rapidxml::xml_document<> doc;
        doc.parse<0>(fdoc.data());
        rapidxml::xml_node<>* config = doc.first_node("config");
        if (config) {
            stat = (int)GetXmlNumber(config, "enable");
            vk[0] = (int)GetXmlNumber(config, "vk0");
            vk[1] = (int)GetXmlNumber(config, "vk1");
            vk[2] = (int)GetXmlNumber(config, "vk2");
        }
    }
    catch (...) {
    }

    QCheckBox* hotkey_title = findChild<QCheckBox*>("checkHotKey");
    hotkey_title->setChecked(stat != 0);
    QPushButton* hotkey_value = findChild<QPushButton*>("hotkeyValue");
    hotkey_value->setEnabled(stat != 0);
    std::string vk_str;
    if (vk[0]) {
        vk_str += GetVkString(vk[0]);
        vk_str += "+";
    }
    if (vk[1]) {
        vk_str += GetVkString(vk[1]);
        vk_str += "+";
    }
    if (vk[2]) {
        vk_str += GetVkString(vk[2]);
        vk_str += "+";
    }
    if (!vk_str.empty()) {
        vk_str.pop_back();
    }
    hotkey_value->setText(vk_str.empty() ? tr("hotkey_default") : vk_str.c_str());
    for (int i = 0; i < 3; i++) {
        hotkey_value->setUserData(i, reinterpret_cast<QObjectUserData*>(vk[i]));
    }
}

void SettingDlg::setupSingal()
{
    QCheckBox* hotkey_title = findChild<QCheckBox*>("checkHotKey");
    connect(hotkey_title, SIGNAL(stateChanged(int)), this, SLOT(OnUseHotKeyChecked(int)));

    QPushButton* save = findChild<QPushButton*>("settingSaveBtn");
    connect(save, SIGNAL(clicked()), this, SLOT(SaveHotKeyConfig()));

    QPushButton* cancel = findChild<QPushButton*>("settingCancelBtn");
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void SettingDlg::OnUseHotKeyChecked(int stat)
{
    QPushButton* hotkey_value = findChild<QPushButton*>("hotkeyValue");
    hotkey_value->setEnabled(stat == Qt::Checked);

    if (stat == Qt::Checked) {
        hotkey_value->setText(tr("reset_hotkey"));
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

void SettingDlg::SaveHotKeyConfig()
{
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<>* root;
    rapidxml::xml_node<>* config;
    rapidxml::xml_node<>* node;
    root = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='UTF-8'"));
    doc.append_node(root);

    config = doc.allocate_node(rapidxml::node_element, doc.allocate_string("config"));
    doc.append_node(config);

    QCheckBox* hotkey_title = findChild<QCheckBox*>("checkHotKey");
    node = doc.allocate_node(rapidxml::node_element, doc.allocate_string("enable"), doc.allocate_string(hotkey_title->isChecked() ? "1" : "0"));
    config->append_node(node);

    QPushButton* hotkey_value = findChild<QPushButton*>("hotkeyValue");
    for (int i = 0; i < 3; i++) {
        int vk = reinterpret_cast<int>(hotkey_value->userData(i));
        std::string vk_i = "vk" + std::to_string(i);
        node = doc.allocate_node(rapidxml::node_element, doc.allocate_string(vk_i.c_str()), doc.allocate_string(std::to_string(vk).c_str()));
        config->append_node(node);
    }

    std::string xml_str;
    rapidxml::print(std::back_inserter(xml_str), doc, 0);
    FILE* fp = fopen(SETTING_XML_NAME, "w+t");
    if (!fp) {
        return;
    }

    fprintf(fp, xml_str.c_str());
    fclose(fp);
}

static int64_t GetXmlNumber(const rapidxml::xml_node<>* node, const char* node_key)
{
    const auto str = GetXmlString(node, node_key);

    return atoll(str.c_str());
}
static std::string GetXmlString(const rapidxml::xml_node<>* node, const char* node_key)
{
    node = node->first_node(node_key);
    if (!node) {
        return "";
    }

    const char* val = node->value();
    if (!val) {
        return "";
    }

    return val;
}

static const char* GetVkString(int vk)
{
    static const char* vk_str[] = {
        "Esc",/*Qt::Key_Escape 0x01000000 */
        "Tab",/*Qt::Key_Tab 0x01000001 */
        "Shift+Tab",/*Qt::Key_Backtab 0x01000002 */
        "BackSpace",/*Qt::Key_Backspace 0x01000003 */
        "Return",/*Qt::Key_Return 0x01000004 */
        "Enter",/*Qt::Key_Enter 0x01000005 Typically located on the keypad.*/
        "Ins",/*Qt::Key_Insert 0x01000006 */
        "Del",/*Qt::Key_Delete 0x01000007 */
        "Pause",/*Qt::Key_Pause 0x01000008 The Pause/Break key (Note: Not anything to do with pausing media)*/

        "Print",/*Qt::Key_Print 0x01000009 */
        "SysReq",/*Qt::Key_SysReq 0x0100000a */
        "Clear",/*Qt::Key_Clear 0x0100000b */

        "Home",/*Qt::Key_Home 0x01000010 */
        "End",/*Qt::Key_End 0x01000011 */
        "Left",/*Qt::Key_Left 0x01000012 */
        "Up",/*Qt::Key_Up 0x01000013 */
        "Right",/*Qt::Key_Right 0x01000014 */
        "Down",/*Qt::Key_Down 0x01000015 */
        "PgUp",/*Qt::Key_PageUp 0x01000016 */
        "PgDown",/*Qt::Key_PageDown 0x01000017 */
        "Shift",/*Qt::Key_Shift 0x01000020 */
        #ifdef Q_OS_WIN
        "Ctrl",/*Qt::Key_Control 0x01000021 On Mac OS X, this corresponds to the Command keys.*/
        "Win",/*Qt::Key_Meta 0x01000022 On Mac OS X, this corresponds to the Control keys. On Windows keyboards, this key is mapped to the Windows key.*/
        #else
        "Control",/*Qt::Key_Meta 0x01000022 On Mac OS X, this corresponds to the Control keys. On Windows keyboards, this key is mapped to the Windows key.*/
        #endif
        "Alt",/*Qt::Key_Alt 0x01000023 */
        "Ctrl+Alt+",/*Qt::Key_AltGr 0x01001103 On Windows, when the KeyDown event for this key is sent, the Ctrl+Alt modifiers are also set.*/
        "CapsLock",/*Qt::Key_CapsLock 0x01000024 */
        "NumLock",/*Qt::Key_NumLock 0x01000025 */
        "ScrollLock",/*Qt::Key_ScrollLock 0x01000026 */

        "F1",/*Qt::Key_F1 0x01000030 */
        "F2",/*Qt::Key_F2 0x01000031 */
        "F3",/*Qt::Key_F3 0x01000032 */
        "F4",/*Qt::Key_F4 0x01000033 */
        "F5",/*Qt::Key_F5 0x01000034 */
        "F6",/*Qt::Key_F6 0x01000035 */
        "F7",/*Qt::Key_F7 0x01000036 */
        "F8",/*Qt::Key_F8 0x01000037 */
        "F9",/*Qt::Key_F9 0x01000038 */
        "F10",/*Qt::Key_F10 0x01000039 */
        "F11",/*Qt::Key_F11 0x0100003a */
        "F12",/*Qt::Key_F12 0x0100003b */
        "F13",/*Qt::Key_F13 0x0100003c */
        "F14",/*Qt::Key_F14 0x0100003d */
        "F15",/*Qt::Key_F15 0x0100003e */
        "F16",/*Qt::Key_F16 0x0100003f */
        "F17",/*Qt::Key_F17 0x01000040 */
        "F18",/*Qt::Key_F18 0x01000041 */
        "F19",/*Qt::Key_F19 0x01000042 */
        "F20",/*Qt::Key_F20 0x01000043 */
        "F21",/*Qt::Key_F21 0x01000044 */
        "F22",/*Qt::Key_F22 0x01000045 */
        "F23",/*Qt::Key_F23 0x01000046 */
        "F24",/*Qt::Key_F24 0x01000047 */
        "F25",/*Qt::Key_F25 0x01000048 */
        /* F25 .. F35 only on X11*/
        "F26",/*Qt::Key_F26 0x01000049 */
        "F27",/*Qt::Key_F27 0x0100004a */
        "F28",/*Qt::Key_F28 0x0100004b */
        "F29",/*Qt::Key_F29 0x0100004c */
        "F30",/*Qt::Key_F30 0x0100004d */
        "F31",/*Qt::Key_F31 0x0100004e */
        "F32",/*Qt::Key_F32 0x0100004f */
        "F33",/*Qt::Key_F33 0x01000050 */
        "F34",/*Qt::Key_F34 0x01000051 */
        "F35",/*Qt::Key_F35 0x01000052 */
        /* extra keys */
        "",/*Qt::Key_Super_L 0x01000053 */
        "",/*Qt::Key_Super_R 0x01000054 */
        "",/*Qt::Key_Menu 0x01000055 */
        "",/*Qt::Key_Hyper_L 0x01000056 */
        "",/*Qt::Key_Hyper_R 0x01000057 */
        "",/*Qt::Key_Help 0x01000058 */
        "",/*Qt::Key_Direction_L 0x01000059 */
        "",/*Qt::Key_Direction_R 0x01000060 */

        "Space",/*Qt::Key_Space 0x20 */
        "Space",/*Qt::Key_Any Key_Space */
        "!",/*Qt::Key_Exclam 0x21 */
        "\"",/*Qt::Key_QuoteDbl 0x22 */
        "#",/*Qt::Key_NumberSign 0x23 */
        "$",/*Qt::Key_Dollar 0x24 */
        "%",/*Qt::Key_Percent 0x25 */
        "&",/*Qt::Key_Ampersand 0x26 */
        "'",/*Qt::Key_Apostrophe 0x27 */
        "(",/*Qt::Key_ParenLeft 0x28 */
        ")",/*Qt::Key_ParenRight 0x29 */
        "*",/*Qt::Key_Asterisk 0x2a */
        "+",/*Qt::Key_Plus 0x2b */
        ",",/*Qt::Key_Comma 0x2c */
        "-",/*Qt::Key_Minus 0x2d */
        ".",/*Qt::Key_Period 0x2e */
        "/",/*Qt::Key_Slash 0x2f */

        "0",/*Qt::Key_0 0x30 */
        "1",/*Qt::Key_1 0x31 */
        "2",/*Qt::Key_2 0x32 */
        "3",/*Qt::Key_3 0x33 */
        "4",/*Qt::Key_4 0x34 */
        "5",/*Qt::Key_5 0x35 */
        "6",/*Qt::Key_6 0x36 */
        "7",/*Qt::Key_7 0x37 */
        "8",/*Qt::Key_8 0x38 */
        "9",/*Qt::Key_9 0x39 */

        ":",/*Qt::Key_Colon 0x3a */
        ";",/*Qt::Key_Semicolon 0x3b */
        "<",/*Qt::Key_Less 0x3c */
        "=",/*Qt::Key_Equal 0x3d */
        ">",/*Qt::Key_Greater 0x3e */
        "?",/*Qt::Key_Question 0x3f */
        "@",/*Qt::Key_At 0x40 */

        "A",/*Qt::Key_A 0x41 */
        "B",/*Qt::Key_B 0x42 */
        "C",/*Qt::Key_C 0x43 */
        "D",/*Qt::Key_D 0x44 */
        "E",/*Qt::Key_E 0x45 */
        "F",/*Qt::Key_F 0x46 */
        "G",/*Qt::Key_G 0x47 */
        "H",/*Qt::Key_H 0x48 */
        "I",/*Qt::Key_I 0x49 */
        "J",/*Qt::Key_J 0x4a */
        "K",/*Qt::Key_K 0x4b */
        "L",/*Qt::Key_L 0x4c */
        "M",/*Qt::Key_M 0x4d */
        "N",/*Qt::Key_N 0x4e */
        "O",/*Qt::Key_O 0x4f */
        "P",/*Qt::Key_P 0x50 */
        "Q",/*Qt::Key_Q 0x51 */
        "R",/*Qt::Key_R 0x52 */
        "S",/*Qt::Key_S 0x53 */
        "T",/*Qt::Key_T 0x54 */
        "U",/*Qt::Key_U 0x55 */
        "V",/*Qt::Key_V 0x56 */
        "W",/*Qt::Key_W 0x57 */
        "X",/*Qt::Key_X 0x58 */
        "Y",/*Qt::Key_Y 0x59 */
        "Z",/*Qt::Key_Z 0x5a */

        "[",/*Qt::Key_BracketLeft 0x5b */
        "\\",/*Qt::Key_Backslash 0x5c */
        "]",/*Qt::Key_BracketRight 0x5d */
        "^",/*Qt::Key_AsciiCircum 0x5e */
        "_",/*Qt::Key_Underscore 0x5f */
        "`",/*Qt::Key_QuoteLeft 0x60 */
        /*0x61-0x7a is the same as 0x41-0x5a*/
        "{",/*Qt::Key_BraceLeft 0x7b */
        "|",/*Qt::Key_Bar 0x7c */
        "}",/*Qt::Key_BraceRight 0x7d */
        "~",/*Qt::Key_AsciiTilde 0x7e */

        /* // Latin 1 codes adapted from X: keysymdef.h */
        "Space(NoBreak)",/*Qt::Key_nobreakspace 0x0a0 127*/
        "€",/*Qt::Key_exclamdown 0x0a1 */
        "",/*Qt::Key_cent 0x0a2 */
        "",/*Qt::Key_sterling 0x0a3 */
        "",/*Qt::Key_currency 0x0a4 */
        "",/*Qt::Key_yen 0x0a5 */
        "",/*Qt::Key_brokenbar 0x0a6 */
        "",/*Qt::Key_section 0x0a7 */
        "",/*Qt::Key_diaeresis 0x0a8 */
        "",/*Qt::Key_copyright 0x0a9 */
        "",/*Qt::Key_ordfeminine 0x0aa */
        "",/*Qt::Key_guillemotleft 0x0ab */
        "",/*Qt::Key_notsign 0x0ac */
        "",/*Qt::Key_hyphen 0x0ad */
        "",/*Qt::Key_registered 0x0ae */
        "",/*Qt::Key_macron 0x0af */
        "",/*Qt::Key_degree 0x0b0 */
        "",/*Qt::Key_plusminus 0x0b1 */
        "",/*Qt::Key_twosuperior 0x0b2 */
        "",/*Qt::Key_threesuperior 0x0b3 */
        "",/*Qt::Key_acute 0x0b4 */
        "",/*Qt::Key_mu 0x0b5 */
        "",/*Qt::Key_paragraph 0x0b6 */
        "",/*Qt::Key_periodcentered 0x0b7 */
        "",/*Qt::Key_cedilla 0x0b8 */
        "",/*Qt::Key_onesuperior 0x0b9 */
        "",/*Qt::Key_masculine 0x0ba */
        "",/*Qt::Key_guillemotright 0x0bb */
        "",/*Qt::Key_onequarter 0x0bc */
        "",/*Qt::Key_onehalf 0x0bd */
        "",/*Qt::Key_threequarters 0x0be */
        "",/*Qt::Key_questiondown 0x0bf */
        "",/*Qt::Key_Agrave 0x0c0 */
        "",/*Qt::Key_Aacute 0x0c1 */
        "",/*Qt::Key_Acircumflex 0x0c2 */
        "",/*Qt::Key_Atilde 0x0c3 */
        "",/*Qt::Key_Adiaeresis 0x0c4 */
        "",/*Qt::Key_Aring 0x0c5 */
        "",/*Qt::Key_AE 0x0c6 */
        "",/*Qt::Key_Ccedilla 0x0c7 */
        "",/*Qt::Key_Egrave 0x0c8 */
        "",/*Qt::Key_Eacute 0x0c9 */
        "",/*Qt::Key_Ecircumflex 0x0ca */
        "",/*Qt::Key_Ediaeresis 0x0cb */
        "",/*Qt::Key_Igrave 0x0cc */
        "",/*Qt::Key_Iacute 0x0cd */
        "",/*Qt::Key_Icircumflex 0x0ce */
        "",/*Qt::Key_Idiaeresis 0x0cf */
        "",/*Qt::Key_ETH 0x0d0 */
        "",/*Qt::Key_Ntilde 0x0d1 */
        "",/*Qt::Key_Ograve 0x0d2 */
        "",/*Qt::Key_Oacute 0x0d3 */
        "",/*Qt::Key_Ocircumflex 0x0d4 */
        "",/*Qt::Key_Otilde 0x0d5 */
        "",/*Qt::Key_Odiaeresis 0x0d6 */
        "",/*Qt::Key_multiply 0x0d7 */
        "",/*Qt::Key_Ooblique 0x0d8 */
        "",/*Qt::Key_Ugrave 0x0d9 */
        "",/*Qt::Key_Uacute 0x0da */
        "",/*Qt::Key_Ucircumflex 0x0db */
        "",/*Qt::Key_Udiaeresis 0x0dc */
        "",/*Qt::Key_Yacute 0x0dd */
        "",/*Qt::Key_THORN 0x0de */
        "",/*Qt::Key_ssharp 0x0df */
        "",/*Qt::Key_division 0x0f7 */
        "",/*Qt::Key_ydiaeresis 0x0ff */
    };

    vk = vk & 0x000000FF;
    if (vk >= sizeof(vk_str) / sizeof(vk_str[0])) {
        return 0;
    }

    return vk_str[vk];
}
