#ifndef CONFIGVALUE_H
#define CONFIGVALUE_H

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include "config/xmlconfig.h"

#include <string>

inline std::string GetConfigString(rapidxml::xml_node<>* node)
{
	const char* str = node->value();
	return str ? str : "";
}

inline uint64_t GetConfigNum(rapidxml::xml_node<>* node)
{
	const char* str = node->value();
	return str ? (uint64_t)atoll(str) : 0;
}

inline std::string GetConfigAttrString(rapidxml::xml_node<>* node, const char* name)
{
	auto attr = node->first_attribute(name);
	const char* value = attr->value();
	return value ? value : "";
}

inline uint64_t GetConfigAttrNum(rapidxml::xml_node<>* node, const char* name)
{
	auto attr = node->first_attribute(name);
	const char* value = attr->value();
	return value ? (uint64_t)atoll(value) : 0;
}

inline void SetConfigStr(rapidxml::xml_node<>* node, const char* name, const char* value)
{
	auto& doc = GetXMLConfig().GetDoc();
	if (name != nullptr)
	{
		auto attr = node->first_attribute(name);
		if (attr)
		{
			attr->value(doc.allocate_string(value));
		}

		return;
	}

	node->value(doc.allocate_string(value));
}

inline void SetConfigNum(rapidxml::xml_node<>* node, const char* name, uint64_t value)
{
	auto& doc = GetXMLConfig().GetDoc();
	if (name != nullptr)
	{
		auto attr = node->first_attribute(name);
		if (attr)
		{
			attr->value(doc.allocate_string(std::to_string(value).c_str()));
		}

		return;
	}

	node->value(doc.allocate_string(std::to_string(value).c_str()));
}

inline void AddConfigAttrStr(rapidxml::xml_node<>* node, const char* name, const char* value)
{
	auto& doc = GetXMLConfig().GetDoc();
	auto attr = doc.allocate_attribute(doc.allocate_string(name), doc.allocate_string(value));
	node->append_attribute(attr);
}

inline void AddConfigAttrStr(rapidxml::xml_node<>* node, const char* name, uint64_t value)
{
	AddConfigAttrStr(node, name, std::to_string(value).c_str());
}

inline void RemoveNode(rapidxml::xml_node<>* root, rapidxml::xml_node<>* node)
{
	root->remove_node(node);
}

#endif // CONFIGVALUE_H
