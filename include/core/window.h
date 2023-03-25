#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "core/input/input.h"

struct GLFWwindow;

namespace vx::core {

struct WindowData {
    std::uint32_t width;
    std::uint32_t height;
    std::string title;
    std::shared_ptr<input::Input> input;
};

class Window {
public:
    Window(std::uint32_t width, std::uint32_t height, const std::string& title,
           const std::shared_ptr<input::Input>& input);
    ~Window();

    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&)                 = delete;
    Window& operator=(Window&&)      = delete;

    void Update() const noexcept;

    [[nodiscard]] bool ShouldClose() const noexcept;

private:
    GLFWwindow* window_ {nullptr};
    WindowData data_;

    void Setup();
};

}  // namespace vx::core