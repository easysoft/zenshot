#ifndef ZTSETTING_LISTITEM_H_
#define ZTSETTING_LISTITEM_H_

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

#define LISTIEM_MIN_HEIGHT 36

class ZTSettingListItem : public QWidget {
	Q_OBJECT

public:
	ZTSettingListItem(QWidget* parent);
	~ZTSettingListItem() {}

	void SetName(const char* txt);
	void SetUrl(const char* url);
	void SetUsr(const char* usr);
	void SetPass(const char* pass);

	const char* GetName() { return name_.c_str(); }
	const char* GetUrl() { return url_.c_str(); }
	const char* GetUsr() { return usr_.c_str(); }
	const char* GetPass() { return pass_.c_str(); }

signals:
	void RemoveItem(ZTSettingListItem* w);

private slots:
	void OnRemoveItem();

protected:
	virtual void enterEvent(QEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;

private:
	void SetupUI();
	void SetupSignal();

private:
	QVBoxLayout m_Layer;
	QLabel m_labelName;
	QPushButton m_btnDel;

	struct // zentao config info
	{
		std::string name_;
		std::string url_;
		std::string usr_;
		std::string pass_;
	};
}; // ZTSettingListItem

#endif // ZTSETTING_LISTITEM_H_
