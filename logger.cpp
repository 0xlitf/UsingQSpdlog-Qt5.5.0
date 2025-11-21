#include "logger.h"

std::shared_ptr<spdlog::logger> createLogger(std::string name) {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.txt");

    auto logger = std::make_shared<spdlog::logger>(name, file_sink);
    logger->set_level(spdlog::level::trace);
    return logger;
}
