#ifndef ZDATAMGR_H
#define ZDATAMGR_H

#include <string>
#include <memory>

struct zdata_header
{
    uint32_t id_;
    std::string name_;
};

struct zdata_header_str
{
    std::string id_;
    std::string name_;
};
using zproduct_item = zdata_header;
using zmodule_item = zdata_header;
using zversion_item = zdata_header;
using ztype_item = zdata_header_str;
using zos_item = zdata_header_str;
using zbrowser_item = zdata_header_str;
using zseverity_item = zdata_header;
using zpri_item = zdata_header;

#endif // ZDATAMGR_H
