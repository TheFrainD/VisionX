#include "core/window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "core/input/input.h"
#include "core/logger.h"

static void glfw_error_callback(int error_code, const char* message) {
    VX_LOG_ERROR("GLFW Error #{}: {}", error_code, message);
}

namespace vx::core {

Window::Window(const std::uint32_t width, const std::uint32_t height, const std::string& title)
    : data_ {width, height, title} {
    Setup();
}

Window::~Window() {
    if (window_) {
        glfwDestroyWindow(window_);
        VX_LOG_DEBUG("Window destroyed");
    }
    glfwTerminate();
    VX_LOG_DEBUG("GLFW terminated");
}

void Window::Setup() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        throw std::runtime_error {"Could not initialize GLFW"};
    }

    VX_LOG_DEBUG("GLFW initialized");

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

    VX_LOG_DEBUG("Window created");

    glfwSetWindowUserPointer(window_, &data_);

    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
        auto* const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data->width      = width;
        data->height     = height;
        glViewport(0, 0, width, height);
    });

    glfwSetKeyCallback(window_, [](GLFWwindow*, int key, int, int action, int) {
        input::Input::keyboard_.keys[key] = (action != GLFW_RELEASE);
    });

    glfwSetMouseButtonCallback(window_, [](GLFWwindow*, int button, int action, int) {
        input::Input::mouse_.buttons[button] = (action != GLFW_RELEASE);
    });

    glfwSetCursorPosCallback(window_, [](GLFWwindow*, double x, double y) {
        input::Input::mouse_.previousPosition = input::Input::mouse_.position;
        input::Input::mouse_.position         = {x, y};
    });

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);  // Enable V-Sync

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(window_);
        glfwTerminate();
        throw std::runtime_error {"Could not initialize GLAD"};
    }

    VX_LOG_DEBUG("GLAD initialized");

    glViewport(0, 0, data_.width, data_.height);

    VX_LOG_DEBUG("Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    VX_LOG_DEBUG("Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    VX_LOG_DEBUG("OpenGL version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    VX_LOG_DEBUG("GLSL version: {}", reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
}

void Window::Update() const noexcept {
    glfwPollEvents();
    glfwSwapBuffers(window_);
}

bool Window::ShouldClose() const noexcept { return glfwWindowShouldClose(window_) != 0; }

}  // namespace vx::core
