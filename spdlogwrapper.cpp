#include "spdlogwrapper.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"  // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h" // support for user defined types

#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace spdlog
{
static logger* logger_;

void spdlog_init(const char* name, const char* file_name, int h, int m, int lv, int flv)
{
    auto console_sink = std::make_shared<sinks::stdout_color_sink_mt>();
    console_sink->set_level(static_cast<level::level_enum>(lv));
    console_sink->set_pattern("[%^%l%$] %v");

    auto file_sink = std::make_shared<sinks::daily_file_sink_mt>(file_name, h, m);
    file_sink->set_level(level::trace);

    logger_ = new logger(name, {console_sink, file_sink});
    logger_->set_level(static_cast<level::level_enum>(lv));
    logger_->flush_on(static_cast<level::level_enum>(flv));
}

logger* logger_ptr()
{
    return logger_;
}
}
