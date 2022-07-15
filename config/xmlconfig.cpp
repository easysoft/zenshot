#include "xmlconfig.h"

#include "spdlogwrapper.hpp"

XMLConfig::XMLConfig()
	: m_File(nullptr)
	, m_Doc()
{
}

void XMLConfig::LoadConfig(const char* file_name)
{
#if XML_CONFIG_THREADSAFE == 1
	std::lock_guard<std::mutex> l__(m_Mutex);
#endif // XML_CONFIG_THREADSAFE
	try 
	{
		m_File.reset(new rapidxml::file<>(file_name));
		m_Doc.parse<0>(const_cast<char*>(m_File->data()));
	}
	catch (...) 
	{
	}
}

void XMLConfig::SaveConfig(const char* file_name)
{
#if XML_CONFIG_THREADSAFE == 1
	std::lock_guard<std::mutex> l__(m_Mutex);
#endif // XML_CONFIG_THREADSAFE
	FILE* fp = fopen(file_name, "w+t");
	if (fp == nullptr) 
	{
		return;
	}

	std::string xml_str;
	rapidxml::print(std::back_inserter(xml_str), m_Doc, 0);
	fprintf(fp, xml_str.c_str());
	fclose(fp);

	L_TRACE("{0}:{1}\n{2}", __FUNCTION__, __LINE__, xml_str.c_str());
}

std::string XMLConfig::GetConfigString3(const char* name, const char* sub_name, const char* attr_name)
{
#if XML_CONFIG_THREADSAFE == 1
	std::lock_guard<std::mutex> l__(m_Mutex);
#endif // XML_CONFIG_THREADSAFE
	rapidxml::xml_node<>* root = m_Doc.first_node(name);
	if (root == nullptr) 
	{
		return "";
	}

	rapidxml::xml_node<>* node = root;
	if (sub_name != nullptr) 
	{
		node = node->first_node(sub_name);
		if (!node) 
		{
			return "";
		}
	}

	const char* value = node->value();
	if (attr_name != nullptr) 
	{
		rapidxml::xml_attribute<>* attr = node->first_attribute(attr_name);
		value = attr->value();
	}
	return value != nullptr ? value : "";
}

std::string XMLConfig::GetConfigString2(const char* name, const char* sub_name)
{
	return GetConfigString3(name, sub_name, nullptr);
}

std::string XMLConfig::GetConfigString1(const char* name)
{
	return GetConfigString2(name, nullptr);
}

uint64_t XMLConfig::GetConfigNum3(const char* name, const char* sub_name, const char* attr_name)
{
	std::string value = GetConfigString3(name, sub_name, attr_name);
	return static_cast<uint64_t>(atoll(value.c_str()));
}

uint64_t XMLConfig::GetConfigNum2(const char* name, const char* sub_name)
{
	std::string value = GetConfigString2(name, sub_name);
	return static_cast<uint64_t>(atoll(value.c_str()));
}

uint64_t XMLConfig::GetConfigNum1(const char* name)
{
	std::string value = GetConfigString1(name);
	return static_cast<uint64_t>(atoll(value.c_str()));
}

void XMLConfig::SetConfigString3(const char* name, const char* sub_name, const char* attr_name, const char* value)
{
#if XML_CONFIG_THREADSAFE == 1
	std::lock_guard<std::mutex> l__(m_Mutex);
#endif // XML_CONFIG_THREADSAFE
	rapidxml::xml_node<>* root = m_Doc.first_node();
	if (root == nullptr) 
	{
		root = m_Doc.allocate_node(rapidxml::node_pi, m_Doc.allocate_string("xml version=\"1.0\" encoding=\"utf-8\""));
		m_Doc.append_node(root);
	}

	root = m_Doc.first_node(name);
	if (root == nullptr) 
	{
		root = m_Doc.allocate_node(rapidxml::node_element, m_Doc.allocate_string(name));
		m_Doc.append_node(root);
	}
	rapidxml::xml_node<>* node = nullptr;
	if (sub_name != nullptr) 
	
	{
		node = root->first_node(sub_name);
		if (node == nullptr) 
		{
			node = m_Doc.allocate_node(rapidxml::node_element, m_Doc.allocate_string(sub_name));
			root->append_node(node);
		}
		else 
		{
			rapidxml::xml_node<>* n = m_Doc.allocate_node(rapidxml::node_element, m_Doc.allocate_string(sub_name));
			root->remove_node(node);
			root->append_node(n);
			node = n;
		}
	}
	else 
	{
		node = root;
	}

	if (attr_name != nullptr) 
	{
		rapidxml::xml_attribute<>* attr = node->first_attribute(m_Doc.allocate_string(attr_name));
		if (attr == nullptr) 
		{
			attr = m_Doc.allocate_attribute(m_Doc.allocate_string(attr_name));
			node->append_attribute(attr);
		}
		attr->value(m_Doc.allocate_string(value));
		return;
	}

	node->value(m_Doc.allocate_string(value));
}

void XMLConfig::SetConfigString2(const char* name, const char* sub_name, const char* value)
{
	SetConfigString3(name, sub_name, nullptr, value);
}

void XMLConfig::SetConfigString1(const char* name, const char* value)
{
	SetConfigString2(name, nullptr, value);
}

void XMLConfig::SetConfigNum3(const char* name, const char* sub_name, const char* attr_name, uint64_t value)
{
	SetConfigString3(name, sub_name, attr_name, std::to_string(value).c_str());
}

void XMLConfig::SetConfigNum2(const char* name, const char* sub_name, uint64_t value)
{
	SetConfigString2(name, sub_name, std::to_string(value).c_str());
}

void XMLConfig::SetConfigNum1(const char* name, uint64_t value)
{
	SetConfigString1(name, std::to_string(value).c_str());
}
