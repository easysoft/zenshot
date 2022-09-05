#include "starterui.h"

#include "starter.h"
#include "config/xmlconfig.h"
#include "spdlogwrapper.hpp"

#include "usrmetatype.h"

#include <QMenu>
#include <QDir>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

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
	if (!m_ZTSubmitDlg.isVisible())
	{
		auto pixmap = w->result();
		m_ZTSubmitDlg.show();
		emit Thumbnail(pixmap);
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

	m_Token.clear();

	std::string uri = build_uri(url->c_str(), "/tokens");

	m_HttpReq.SetUrl(uri.c_str());
	m_HttpReq.SetPost("{\"account\": \"%s\", \"password\": \"%s\"}", usr->c_str(), pass->c_str());

	std::string data;
	if (!m_HttpReq.Exec(data)) // http error
	{
		return;
	}

	QJsonParseError e;
	QJsonDocument doc = QJsonDocument::fromJson(data.c_str(), &e);
	if (doc.isNull() || e.error != QJsonParseError::NoError)
	{
// 		QMessageBox::information(NULL, tr("Title"), tr("invalid_usr"));
		return;
	}

	if (doc["error"].isString())
	{
// 		QMessageBox::information(NULL, tr("Title"), doc["error"].toString().toUtf8());
		return;
	}

	auto token = doc["token"].toString();
	if (token.isEmpty())
	{
// 		QMessageBox::information(NULL, tr("Title"), tr("invalid_usr"));
		return;
	}
	m_Token = token.toStdString();
}

void StarterUI::OnProduct(string_ptr url)
{
	std::string uri = build_uri(url->c_str(), "/products");
	m_HttpReq.SetUrl(uri.c_str());
}

#endif // NZENTAO_VER_
