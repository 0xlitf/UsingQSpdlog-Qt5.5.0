#ifndef LOGGER_H
#define LOGGER_H

#include "qspdlog/qabstract_spdlog_toolbar.hpp"
#include "qspdlog/qspdlog.hpp"
#include "qspdlog/qspdlog_toolbar.hpp"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

std::shared_ptr<spdlog::logger> createLogger(std::string name);

#endif // LOGGER_H
