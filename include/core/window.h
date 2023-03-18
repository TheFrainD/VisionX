#pragma once

#include <cstdint>
#include <string>

struct GLFWwindow;

namespace vx::core {

struct WindowData {
    std::uint32_t width;
    std::uint32_t height;
    std::string title;
};

class Window {
public:
    Window(std::uint32_t width, std::uint32_t height, const std::string& title);
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