#ifndef XML_CONFIG_H
#define XML_CONFIG_H

#define XML_CONFIG_THREADSAFE 0

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <memory>

#include <string>
#if XML_CONFIG_THREADSAFE == 1
#include <mutex>
#endif // XML_CONFIG_THREADSAFE

extern std::string SETTING_XML_NAME;

class XMLConfig {
public:
	XMLConfig();
	~XMLConfig() {}

	void LoadConfig(const std::string& file_name);
	void SaveConfig(const std::string& file_name);
	
	// read: <config> <setting enable="1"/></config>
	std::string GetConfigString3(const char* name, const char* sub_name, const char* attr_name);
	// read: <config> <enable>1</enable></config>
	std::string GetConfigString2(const char* name, const char* sub_name);
	// read: <config>1</config>
	std::string GetConfigString1(const char* name);

	uint64_t GetConfigNum3(const char* name, const char* sub_name, const char* attr_name);
	uint64_t GetConfigNum2(const char* name, const char* sub_name);
	uint64_t GetConfigNum1(const char* name);

	// set: <config> <setting enable="1"/></config>
	void SetConfigString3(const char* name, const char* sub_name, const char* attr_name, const char* value);
	// set: <config> <enable>1</enable></config>
	void SetConfigString2(const char* name, const char* sub_name, const char* value);
	// set: <config>1</config>
	void SetConfigString1(const char* name, const char* value);

	void SetConfigNum3(const char* name, const char* sub_name, const char* attr_name, uint64_t value);
	void SetConfigNum2(const char* name, const char* sub_name, uint64_t value);
	void SetConfigNum1(const char* name, uint64_t value);

	void RemoveConfig3(const char* name, const char* sub_name, const char* attr_name);
	void RemoveConfig2(const char* name, const char* sub_name);
	void RemoveConfig1(const char* name);
private:
#if XML_CONFIG_THREADSAFE == 1
	std::mutex m_Mutex;
#endif // XML_CONFIG_THREADSAFE
	std::shared_ptr<rapidxml::file<>> m_File;
	rapidxml::xml_document<> m_Doc;
};

inline XMLConfig& GetXMLConfig()
{
	static XMLConfig config;
	return config;
}

// just for <zentaox name="1" url="" usr="" pass=""/>
inline std::string BuildConfigKey(int index)
{
	return "zentao" + std::to_string(index);
}

#endif // XML_CONFIG_H
