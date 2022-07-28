#ifndef SPDLOGWRAPPER_HPP
#define SPDLOGWRAPPER_HPP

#include "spdlog/spdlog.h"

namespace spdlog
{
void spdlog_init(const char* name, const char* file_name, int h, int m, int lv, int flv);
logger* logger_ptr();
} // spdlog

#ifdef USE_SPDLOG_
#define L_TRACE(fmt, ...)	spdlog::logger_ptr()->trace(fmt, ##__VA_ARGS__);
#define L_DEBUG(fmt, ...)	spdlog::logger_ptr()->debug(fmt, ##__VA_ARGS__);
#define L_INFO(fmt, ...)		spdlog::logger_ptr()->info(fmt, ##__VA_ARGS__);
#define L_WARN(fmt, ...)		spdlog::logger_ptr()->warn(fmt, ##__VA_ARGS__);
#define L_ERROR(fmt, ...)	spdlog::logger_ptr()->error(fmt, ##__VA_ARGS__);
#define L_CRITICAL(fmt, ...) spdlog::logger_ptr()->critical(fmt, ##__VA_ARGS__);
#define L_FUNCTION()	L_TRACE("function: {0} @ line: {1}", __FUNCTION__, __LINE__);
#else
#define L_TRACE(...) 
#define L_DEBUG(...) 
#define L_INFO(...) 
#define L_WARN(...) 
#define L_ERR(...) 
#define L_CRITICAL(...) 
#define L_FUNCTION()
#endif // USE_SPDLOG_

#endif // SPDLOGWRAPPER_HPP
