#include "core/logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <vector>

namespace vx::core {

std::shared_ptr<spdlog::logger> Logger::logger_;

void Logger::Setup(const std::string& filename) {
    std::vector<spdlog::sink_ptr> sinks;

    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.back()->set_level(spdlog::level::trace);

    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true));
    sinks.back()->set_level(spdlog::level::trace);

    logger_ = std::make_shared<spdlog::logger>("VisionX Logger", std::begin(sinks), std::end(sinks));
    logger_->set_pattern("%^[%X] %l: %v%$");
    logger_->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Logger::Get() { return logger_; }

}  // namespace vx::core