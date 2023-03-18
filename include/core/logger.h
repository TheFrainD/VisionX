#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

namespace vx::core {

class Logger {
public:
    Logger() = delete;

    static void Setup(const std::string& filename);
    static std::shared_ptr<spdlog::logger>& Get();

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

}  // namespace vx::core

#define VX_LOG_TRACE(...)    ::vx::core::Logger::Get()->trace(__VA_ARGS__)
#define VX_LOG_DEBUG(...)    ::vx::core::Logger::Get()->debug(__VA_ARGS__)
#define VX_LOG_INFO(...)     ::vx::core::Logger::Get()->info(__VA_ARGS__)
#define VX_LOG_WARN(...)     ::vx::core::Logger::Get()->warn(__VA_ARGS__)
#define VX_LOG_ERROR(...)    ::vx::core::Logger::Get()->error(__VA_ARGS__)
#define VX_LOG_CRITICAL(...) ::vx::core::Logger::Get()->critical(__VA_ARGS__)
