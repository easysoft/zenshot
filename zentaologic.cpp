#include "starterui.h"

#include "starter.h"
#include "config/xmlconfig.h"
#include "config/configvalue.h"
#include "spdlogwrapper.hpp"

#include "usrmetatype.h"

#include <QMenu>
#include <QDir>
#include <QMessageBox>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QBuffer>

#include <QDesktopServices>

#if !NZENTAO_VER_
void StarterUI::OnShowZenTaoSetting()
{
	if (!m_ZTSettingDlg.isVisible())
	{
		m_ZTSettingDlg.show();
	}

	m_ZTSettingDlg.raise();
	m_ZTSettingDlg.activateWindow();
}

void StarterUI::OnShowPreview(Workspace* w)
{
    bool has_config = false;
    auto cb = [&](rapidxml::xml_node<>*& root, rapidxml::xml_node<>*& node)
    {
        (void*)root;
        (void*)node;

        has_config = true;
        return true;
    };
    GetXMLConfig().FindAllNode("config", "zentao", cb);
    if (!has_config)
    {
        m_ZTSettingDlg.show();
        m_ZTSettingDlg.raise();
        m_ZTSettingDlg.activateWindow();
        return;
    }

	if (!m_ZTSubmitDlg.isVisible())
	{
        m_CurrentShot = w->result();
		m_ZTSubmitDlg.show();
		emit Thumbnail(m_CurrentShot);
	}

	m_ZTSubmitDlg.raise();
	m_ZTSubmitDlg.activateWindow();
}

void StarterUI::OnLogin(string_ptr url, string_ptr usr, string_ptr pass)
{
	if (IsSameUsr(*usr, *url))
	{
		return;
	}

    QString err_token;
    if (UsrLogin(url, usr, pass, err_token))
    {
        QMessageBox::information(NULL, tr("Title"), err_token);
        return;
    }

    m_HttpReq.SetToken(err_token.toStdString().c_str());
}

void StarterUI::OnSubmitLogin(string_ptr name)
{
    string_ptr url, usr, pass;
    auto cb = [&](rapidxml::xml_node<>*& root, rapidxml::xml_node<>*& node)
    {
        (void*)root;
        if (GetConfigAttrString(node, "name") == *name)
        {
            url.reset(new std::string(GetConfigAttrString(node, "url")));
            usr.reset(new std::string(GetConfigAttrString(node, "usr")));
            pass.reset(new std::string(GetConfigAttrString(node, "pass")));
            return true;
        }
        return false;
    };
    GetXMLConfig().FindAllNode("config", "zentao", cb);

    if (url == nullptr || usr == nullptr || pass == nullptr)
    {
        SubmitLoginResult(false);
        return;
    }

    if (url->empty() || usr->empty() || pass->empty())
    {
        SubmitLoginResult(false);
        return;
    }

//     if (IsSameUsr(*usr, *url))
//     {
//         SubmitLoginResult(true);
//         return;
//     }

    QString err_token;
    if (UsrLogin(url, usr, pass, err_token))
    {
        QMessageBox::information(NULL, tr("Title"), err_token);
        SubmitLoginResult(false);
        return;
    }

    m_HttpReq.SetToken(err_token.toStdString().c_str());
    SubmitLoginResult(true);
}

void StarterUI::OnHttpProduct()
{
    zproduct_item_vec_ptr items(new std::vector<zproduct_item>);
	std::string orig_uri = build_uri(m_CurrentUrl.c_str(), "/products");
    for (int i = 1; i; i++)
    {
        std::string uri = orig_uri;
        uri.append("?")
            .append("limit=50")
            .append("&")
            .append("page=").append(std::to_string(i));
        m_HttpReq.SetUrl(uri.c_str());
        m_HttpReq.SetTokenHeader();

        std::string data;
        if (!m_HttpReq.Exec(data))
        {
            return;
        }

        L_TRACE(data.c_str());

        QJsonParseError e;
        QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
        if (doc.isNull() || e.error != QJsonParseError::NoError)
        {
            break;
        }

        auto products = doc["products"].toArray();
        for (const auto& item : products)
        {
            auto obj = item.toObject();

            zproduct_item product;

            product.id_ = static_cast<uint32_t>(obj["id"].toInt());
            product.name_ = obj["name"].toString().toStdString();
            items->push_back(product);
        }

        int total = doc["total"].toInt();
        int limit = doc["limit"].toInt();
        int max_page = total / limit;
        if (total % limit) max_page++;
        if (i >= max_page)
            break;
    }

    emit ProductItems(items);
}

void StarterUI::OnHttpModule(uint32_t product_id, string_ptr view_type)
{
    zmodule_item_vec_ptr items(new std::vector<zmodule_item>);
    std::string orig_uri = build_uri(m_CurrentUrl.c_str(), "/modules");
    std::string uri = orig_uri;
    uri.append("?")
        .append("id=").append(std::to_string(product_id))
        .append("&")
        .append("type=").append(*view_type);
    m_HttpReq.SetUrl(uri.c_str());
    m_HttpReq.SetTokenHeader();

    std::string data;
    if (!m_HttpReq.Exec(data))
    {
        emit ModuleItems(items);
        return;
    }

    L_TRACE(data.c_str());

    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
    if (doc.isNull() || e.error != QJsonParseError::NoError)
    {
        emit ModuleItems(items);
        return;
    }

    auto modules = doc["modules"].toArray();
    for (const auto& item : modules)
    {
        auto obj = item.toObject();

        zmodule_item product;

        product.id_ = static_cast<uint32_t>(obj["id"].toInt());
        product.name_ = obj["name"].toString().toStdString();
        items->push_back(product);
    }

    emit ModuleItems(items);
}

void StarterUI::OnHttpVersion(uint32_t product_id, string_ptr type)
{
    zversion_item_vec_ptr items(new std::vector<zversion_item>);
    std::string uri = build_uri(m_CurrentUrl.c_str(), "/projects");
    uri.append("/").append(std::to_string(product_id))
        .append("/builds");
    m_HttpReq.SetUrl(uri.c_str());
    m_HttpReq.SetTokenHeader();

    std::string data;
    if (!m_HttpReq.Exec(data))
    {
        emit VersionItems(items);
        return;
    }

    L_TRACE(data.c_str());

    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
    if (doc.isNull() || e.error != QJsonParseError::NoError)
    {
        emit VersionItems(items);
        return;
    }

    auto modules = doc["builds"].toArray();
    for (const auto& item : modules)
    {
        auto obj = item.toObject();

        zversion_item product;

        product.id_ = obj["branchName"].toString().toStdString();
        product.name_ = obj["name"].toString().toStdString();
        items->push_back(product);
    }

    emit VersionItems(items);
}

void StarterUI::OnHttpModules(string_ptr type)
{
    zpri_item_vec_ptr pris(new std::vector<zpri_item>);
    zseverity_item_vec_ptr serveritys(new std::vector<zseverity_item>);
    zos_item_vec_ptr oss(new std::vector<zos_item>);
    zbrowser_item_vec_ptr browers(new std::vector<zbrowser_item>);
    ztype_item_vec_ptr types(new std::vector<ztype_item>);
    std::string uri = build_uri(m_CurrentUrl.c_str(), "/langs");
    uri.append("?")
        .append("modules=").append(*type);
    m_HttpReq.SetUrl(uri.c_str());
    m_HttpReq.SetTokenHeader();

    std::string data;
    if (!m_HttpReq.Exec(data))
    {
        emit ModulesItems(pris, serveritys, oss, browers, types);
        return;
    }

    L_TRACE(data.c_str());

    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
    if (doc.isNull() || e.error != QJsonParseError::NoError)
    {
        emit ModulesItems(pris, serveritys, oss, browers, types);
        return;
    }

    auto modules = doc[type->c_str()].toObject();
    auto priList = modules["priList"].toArray();
    auto severityList = modules["severityList"].toObject();
    auto osList = modules["osList"].toObject();
    auto browserList = modules["browserList"].toObject();
    auto versionList = modules["versionList"].toArray();
    auto typeList = modules["typeList"].toObject();
    auto categoryList = modules["categoryList"].toObject();

    for (const auto& pri : priList)
    {
        zpri_item item;
        item.name_ = pri.toString().toStdString();
        item.id_ = static_cast<uint32_t>(atoi(item.name_.c_str()));

        pris->push_back(item);
    }

    for (auto it = severityList.begin(); it != severityList.end(); it++)
    {
        zseverity_item item;
        item.id_ = static_cast<uint32_t>(it.key().toInt());
        item.name_ = it.value().toString().toStdString();

        serveritys->push_back(item);
    }

    for (auto it = osList.begin(); it != osList.end(); it++)
    {
        zos_item item;
        item.id_ = it.key().toStdString();
        item.name_ = it.value().toString().toStdString();

        oss->push_back(item);
    }

    for (auto it = browserList.begin(); it != browserList.end(); it++)
    {
        zbrowser_item item;
        item.id_ = it.key().toStdString();
        item.name_ = it.value().toString().toStdString();

        browers->push_back(item);
    }

    for (auto it = typeList.begin(); it != typeList.end(); it++)
    {
        ztype_item item;
        item.id_ = it.key().toStdString();
        item.name_ = it.value().toString().toStdString();

        types->push_back(item);
    }
    for (auto it = categoryList.begin(); it != categoryList.end(); it++)
    {
        ztype_item item;
        item.id_ = it.key().toStdString();
        item.name_ = it.value().toString().toStdString();

        types->push_back(item);
    }

    emit ModulesItems(pris, serveritys, oss, browers, types);
}

void StarterUI::OnSubmitDemandJson(uint32_t product_id, string_ptr json)
{
    std::string demand_uri;
    demand_uri.append("/products/").append(std::to_string(product_id))
        .append("/stories");
    std::string uri = build_uri(m_CurrentUrl.c_str(), demand_uri.c_str());

    m_HttpReq.SetUrl(uri.c_str());
    m_HttpReq.SetTokenHeader();
    m_HttpReq.SetPost(json->c_str());

    std::string data;
    if (!m_HttpReq.Exec(data)) // http error
    {
        return;
    }

    bool success = false;
    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
    if (doc.isNull() || e.error != QJsonParseError::NoError)
    {
		m_ZTTipsDlg.SetContent(false, tr("demandunknown"));
	}
	else if (doc["id"].isUndefined() || doc["id"].isNull())
    {
        auto title = doc["error"].toObject();
        auto arr = title["title"].toArray();
        if (!arr.isEmpty())
        {
            m_ZTTipsDlg.SetContent(false, arr[0].toString());
        }
        else
        {
            m_ZTTipsDlg.SetContent(false, tr("demandunknown"));
        }
    }
    else
    {
        m_LastSubmitUrl = "story-view-";
        m_LastSubmitUrl.append(std::to_string(doc["id"].toInt())).append(".html");

        m_ZTTipsDlg.SetContent(true, tr("demandsuccess"));
        success = true;
    }
    int ret = m_ZTTipsDlg.exec();

	if (success)
	{
		m_ZTSubmitDlg.hide();
        emit StopShot(m_CurrentStarter);
		return;
	}

	if (ret != 1)
	{
		m_ZTSubmitDlg.hide();
        return;
	}
}

void StarterUI::OnSubmitBugJson(uint32_t product_id, string_ptr json)
{
    std::string bug_uri;
    bug_uri.append("/products/").append(std::to_string(product_id))
        .append("/bugs");
    std::string uri = build_uri(m_CurrentUrl.c_str(), bug_uri.c_str());

    m_HttpReq.SetUrl(uri.c_str());
    m_HttpReq.SetTokenHeader();
    m_HttpReq.SetPost(json->c_str());

    L_TRACE(json->c_str());

    std::string data;
    if (!m_HttpReq.Exec(data)) // http error
    {
        return;
    }

    bool success = false;
    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
    if (doc.isNull() || e.error != QJsonParseError::NoError)
    {
        m_ZTTipsDlg.SetContent(false, tr("bugunknown"));
    }
    else if (doc["id"].isUndefined() || doc["id"].isNull())
	{
		auto title = doc["error"].toObject();
		auto arr = title["title"].toArray();
		if (!arr.isEmpty())
		{
			m_ZTTipsDlg.SetContent(false, arr[0].toString());
		}
        else
        {
            m_ZTTipsDlg.SetContent(false, tr("bugunknown"));
        }
	}
	else
	{
        m_LastSubmitUrl = "bug-view-";
        m_LastSubmitUrl.append(std::to_string(doc["id"].toInt())).append(".html");

		m_ZTTipsDlg.SetContent(true, tr("bugsuccess"));
        success = true;
	}
	int ret = m_ZTTipsDlg.exec();

    if (success)
    {
        m_ZTSubmitDlg.hide();
        emit StopShot(m_CurrentStarter);
        return;
    }

	if (ret != 1)
	{
		m_ZTSubmitDlg.hide();
		return;
	}
}

void StarterUI::OnUploadImage()
{
    if (m_CurrentShot == nullptr)
    {
        emit UploadImageDone(false, nullptr);
        return;
    }
    QByteArray pix_bytes;
    QBuffer buf(&pix_bytes);
    if (!m_CurrentShot->save(&buf, "png") || pix_bytes.isEmpty())
    {
        emit UploadImageDone(false, nullptr);
        return;
    }
    std::string uri = build_uri(m_CurrentUrl.c_str(), "/files");
    m_HttpReq.SetUrl(uri.c_str());
    m_HttpReq.SetTokenHeader();

    std::string data;
    if (!m_HttpReq.UploadFormFile(data, pix_bytes)) // http error
    {
        emit UploadImageDone(false, nullptr);
        return;
    }

    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
    if (doc.isNull() || e.error != QJsonParseError::NoError)
    {
        emit UploadImageDone(false, nullptr);
        return;
    }

    if (doc["error"].isString())
    {
        QMessageBox::information(NULL, tr("Title"), doc["error"].toString().toUtf8());
        emit UploadImageDone(false, nullptr);
        return;
    }

    string_ptr img_url(new std::string(doc["url"].toString().toStdString()));
    emit UploadImageDone(true, img_url);
}

void StarterUI::OnOpenZentaoUrl()
{
    QString url = m_CurrentUrl.c_str();
    if (*m_CurrentUrl.rbegin() != '/')
    {
        url += "/";
    }
    url += m_LastSubmitUrl.c_str();
    QDesktopServices::openUrl(QUrl(url));
}

void StarterUI::OnSubmitZentaoHide()
{
    if (m_CurrentStarter == nullptr)
        return;
    
    m_CurrentStarter->rasie();
}

void StarterUI::OnTipZentaoHide()
{
    m_ZTSubmitDlg.raise();
    m_ZTSubmitDlg.activateWindow();
}

int StarterUI::UsrLogin(string_ptr url, string_ptr usr, string_ptr pass, QString& err_token)
{
    std::string uri = build_uri(url->c_str(), "/tokens");

    m_HttpReq.SetUrl(uri.c_str());
    m_HttpReq.SetPost("{\"account\": \"%s\", \"password\": \"%s\"}", usr->c_str(), pass->c_str());

    std::string data;
    if (!m_HttpReq.Exec(data)) // http error
    {
        err_token = tr("httptimeout");
        return -1;
    }

    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
    if (doc.isNull() || e.error != QJsonParseError::NoError)
    {
        err_token = tr("invalidjson");
        return -2;
    }

    if (doc["error"].isString())
    {
        err_token = doc["error"].toString().toUtf8();
        return -3;
    }

    auto token = doc["token"].toString();
    if (token.isEmpty())
    {
        err_token = tr("invalidtoken");
        return -4;
    }

    m_CurrentUsr = *usr;
    m_CurrentUrl = *url;

    err_token = token;

    return 0;
}

#endif // NZENTAO_VER_
