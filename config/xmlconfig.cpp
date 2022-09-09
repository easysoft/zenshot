#include "xmlconfig.h"

#include "spdlogwrapper.hpp"

std::string SETTING_XML_NAME = "./setting.xml";

XMLConfig::XMLConfig()
	: m_File(nullptr)
	, m_Doc()
{
}

void XMLConfig::LoadConfig(const std::string& file_name)
{
	try
	{
		m_File.reset(new rapidxml::file<>(file_name.c_str()));
		m_Doc.parse<rapidxml::parse_no_data_nodes>(const_cast<char*>(m_File->data()));
	}
	catch (...) 
	{
	}
}

void XMLConfig::SaveConfig(const std::string& file_name)
{
	FILE* fp = fopen(file_name.c_str(), "w+t");
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

std::string XMLConfig::GetConfigString1(const char* name)
{
	return GetConfigString2(name, nullptr);
}

std::string XMLConfig::GetConfigString2(const char* name, const char* sub_name)
{
	return GetConfigString3(name, sub_name, nullptr);
}

std::string XMLConfig::GetConfigString3(const char* name, const char* sub_name, const char* attr_name)
{
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

uint64_t XMLConfig::GetConfigNum1(const char* name)
{
	std::string value = GetConfigString1(name);
	return static_cast<uint64_t>(atoll(value.c_str()));
}

uint64_t XMLConfig::GetConfigNum2(const char* name, const char* sub_name)
{
	std::string value = GetConfigString2(name, sub_name);
	return static_cast<uint64_t>(atoll(value.c_str()));
}

uint64_t XMLConfig::GetConfigNum3(const char* name, const char* sub_name, const char* attr_name)
{
	std::string value = GetConfigString3(name, sub_name, attr_name);
	return static_cast<uint64_t>(atoll(value.c_str()));
}

void XMLConfig::FindAllNode(const char* name, const char* sub_name, const std::function<bool(rapidxml::xml_node<>*& root, rapidxml::xml_node<>*& node)>& cb)
{
	rapidxml::xml_node<>* root = m_Doc.first_node();
	rapidxml::xml_node<>* node = m_Doc.first_node(name);
	if (root == nullptr || node == nullptr)
		return;

	if (sub_name != nullptr)
	{
		for (node = node->first_node(sub_name); node; node = node->next_sibling(sub_name))
		{
			if (cb(root, node))
			{
				break;
			}
		}
		return;
	}

	for (node; node; node = node->next_sibling(m_Doc.allocate_string(name)))
	{
		if (cb(root, node))
		{
			break;
		}
	}
}

void XMLConfig::RemoveAllNode(const char* name, const char* sub_name)
{
	rapidxml::xml_node<>* root = m_Doc.first_node(name);
	if (root == nullptr)
	{
		return;
	}
	if (sub_name == nullptr)
	{
		root->remove_all_nodes();
		return;
	}

	for (rapidxml::xml_node<>* node = root->last_node(sub_name); node; node = root->last_node(sub_name))
	{
		root->remove_node(node);
	}
}

rapidxml::xml_node<>* XMLConfig::AddConfigString1(const char* name, const char* value)
{
	return AddConfigString2(name, nullptr, value);
}

rapidxml::xml_node<>* XMLConfig::AddConfigString2(const char* name, const char* sub_name, const char* value)
{
	return AddConfigString3(name, sub_name, nullptr, value);
}

rapidxml::xml_node<>* XMLConfig::AddConfigString3(const char* name, const char* sub_name, const char* attr_name, const char* value)
{
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
		node = m_Doc.allocate_node(rapidxml::node_element, m_Doc.allocate_string(sub_name));
		root->append_node(node);
	}
	else
	{
		node = root;
	}
	
	if (attr_name != nullptr)
	{
		rapidxml::xml_attribute<>* attr = m_Doc.allocate_attribute(m_Doc.allocate_string(attr_name));
		node->append_attribute(attr);
		attr->value(m_Doc.allocate_string(value));
	}
	else
	{
		node->value(m_Doc.allocate_string(value));
	}

	return node;
}

rapidxml::xml_node<>* XMLConfig::AddConfigNum1(const char* name, uint64_t value)
{
	return AddConfigNum2(name, nullptr, value);
}

rapidxml::xml_node<>* XMLConfig::AddConfigNum2(const char* name, const char* sub_name, uint64_t value)
{
	return AddConfigNum3(name, sub_name,nullptr, value);
}

rapidxml::xml_node<>* XMLConfig::AddConfigNum3(const char* name, const char* sub_name, const char* attr_name, uint64_t value)
{
	return AddConfigString3(name, sub_name, attr_name, std::to_string(value).c_str());
}
