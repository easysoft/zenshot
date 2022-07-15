#ifndef SPDLOGWRAPPER_HPP
#define SPDLOGWRAPPER_HPP

#include "spdlog/spdlog.h"

namespace spdlog
{
void spdlog_init(const char* name, const char* file_name, int h, int m, int lv, int flv);
logger* logger_ptr();
} // spdlog

#ifdef USE_SPDLOG_
#define L_TRACE(...)	spdlog::logger_ptr()->trace(##__VA_ARGS__)
#define L_DEBUG(...)	spdlog::logger_ptr()->debug(##__VA_ARGS__)
#define L_INFO(...)		spdlog::logger_ptr()->info(##__VA_ARGS__)
#define L_WARN(...)		spdlog::logger_ptr()->warn(##__VA_ARGS__)
#define L_ERROR(...)	spdlog::logger_ptr()->error(##__VA_ARGS__)
#define L_CRITICAL(...) spdlog::logger_ptr()->critical(##__VA_ARGS__)
#else
#define L_TRACE(...) 
#define L_DEBUG(...) 
#define L_INFO(...) 
#define L_WARN(...) 
#define L_ERR(...) 
#define L_CRITICAL(...) 
#endif // USE_SPDLOG_

#endif // SPDLOGWRAPPER_HPP
