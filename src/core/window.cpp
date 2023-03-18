#include "core/window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

static void glfw_error_callback(int error_code, const char* message) {
    std::cerr << "GLFW Error #" << error_code << ": " << message << std::endl;
}

namespace vx::core {

Window::Window(const std::uint32_t width, const std::uint32_t height, const std::string& title)
    : data_ {width, height, title} {
    Setup();
}

Window::~Window() {
    if (window_) {
        glfwDestroyWindow(window_);
    }
    glfwTerminate();
}

void Window::Setup() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        throw std::runtime_error {"Could not initialize GLFW"};
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), nullptr, nullptr);
    if (!window_) {
        glfwTerminate();
        throw std::runtime_error {"Could not create window"};
    }

    glfwSetWindowUserPointer(window_, &data_);

    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
        auto* const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data->width      = width;
        data->height     = height;
        glViewport(0, 0, width, height);
    });

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);  // Enable V-Sync

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(window_);
        glfwTerminate();
        throw std::runtime_error {"Could not initialize GLAD"};
    }

    glViewport(0, 0, data_.width, data_.height);
}

void Window::Update() const noexcept {
    glfwPollEvents();
    glfwSwapBuffers(window_);
}

bool Window::ShouldClose() const noexcept { return glfwWindowShouldClose(window_) != 0; }

}  // namespace vx::core
