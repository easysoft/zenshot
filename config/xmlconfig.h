#ifndef XML_CONFIG_H
#define XML_CONFIG_H

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <memory>
#include <functional>

#include <string>

extern std::string SETTING_XML_NAME;

class XMLConfig {
public:
	XMLConfig();
	~XMLConfig() {}

	void LoadConfig(const std::string& file_name);
	void SaveConfig(const std::string& file_name);

	rapidxml::xml_document<>& GetDoc() { return m_Doc; }
	
	// read: <config>1</config>
	std::string GetConfigString1(const char* name);
	// read: <config> <enable>1</enable></config>
	std::string GetConfigString2(const char* name, const char* sub_name);
	// read: <config> <setting enable="1"/></config>
	std::string GetConfigString3(const char* name, const char* sub_name, const char* attr_name);

	uint64_t GetConfigNum1(const char* name);
	uint64_t GetConfigNum2(const char* name, const char* sub_name);
	uint64_t GetConfigNum3(const char* name, const char* sub_name, const char* attr_name);

	void FindAllNode(const char* name, const char* sub_name, const std::function<bool(rapidxml::xml_node<>* root, rapidxml::xml_node<>* node)>& cb);
	void RemoveAllNode(const char* name, const char* sub_name);

	// set: <config>1</config>
	rapidxml::xml_node<>* AddConfigString1(const char* name, const char* value);
	// set: <config> <enable>1</enable></config>
	rapidxml::xml_node<>* AddConfigString2(const char* name, const char* sub_name, const char* value);
	// set: <config> <setting enable="1"/></config>
	rapidxml::xml_node<>* AddConfigString3(const char* name, const char* sub_name, const char* attr_name, const char* value);

	rapidxml::xml_node<>* AddConfigNum1(const char* name, uint64_t value);
	rapidxml::xml_node<>* AddConfigNum2(const char* name, const char* sub_name, uint64_t value);
	rapidxml::xml_node<>* AddConfigNum3(const char* name, const char* sub_name, const char* attr_name, uint64_t value);
private:
	std::shared_ptr<rapidxml::file<>> m_File;
	rapidxml::xml_document<> m_Doc;
};

inline XMLConfig& GetXMLConfig()
{
	static XMLConfig config;
	return config;
}

#endif // XML_CONFIG_H
