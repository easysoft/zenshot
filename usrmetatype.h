#pragma once

#if !NZENTAO_VER_
#include "zdata/zdataitem.h"
#endif // NZENTAO_VER_

#include <string>
#include <vector>
#include <memory>

using string_ptr = std::shared_ptr<std::string>;
#if !NZENTAO_VER_
using zproduct_item_vec_ptr = std::shared_ptr<std::vector<zproduct_item>>;
using zmodule_item_vec_ptr = std::shared_ptr<std::vector<zmodule_item>>;
using zversion_item_vec_ptr = std::shared_ptr<std::vector<zversion_item>>;
using ztype_item_vec_ptr = std::shared_ptr<std::vector<ztype_item>>;
using zos_item_vec_ptr = std::shared_ptr<std::vector<zos_item>>;
using zbrowser_item_vec_ptr = std::shared_ptr<std::vector<zbrowser_item>>;
using zseverity_item_vec_ptr = std::shared_ptr<std::vector<zseverity_item>>;
using zpri_item_vec_ptr = std::shared_ptr<std::vector<zpri_item>>;
#endif // NZENTAO_VER_
