#include "ogl/shader.h"

#include <glad/glad.h>

namespace vx::ogl {

Shader::Shader(const ShaderType type) { id_ = glCreateShader(static_cast<GLenum>(type)); }

Shader::Shader(const ShaderType type, const std::string& source) {
    id_ = glCreateShader(static_cast<GLenum>(type));
    SetSource(source);
    Compile();
}

Shader::~Shader() { Release(); }

Shader::Shader(Shader&& other) noexcept : id_(other.id_) { id_ = 0; }

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        Release();

        std::swap(id_, other.id_);
    }

    return *this;
}

void Shader::SetSource(const std::string& source) const noexcept {
    const auto* c_source = source.c_str();
    glShaderSource(id_, 1, &c_source, nullptr);
}

void Shader::Compile() const {
    glCompileShader(id_);

    GLint compile_status;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
        throw ShaderCompilationException {GetInfoLog()};
    }
}

void Shader::Release() noexcept {
    glDeleteShader(id_);
    id_ = 0;
}

std::string Shader::GetInfoLog() const noexcept {
    GLint length;
    glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &length);

    if (length > 0) {
        std::string info_log(length, 0);
        glGetShaderInfoLog(id_, length, &length, info_log.data());
        return info_log;
    }

    return {};
}

std::uint32_t Shader::GetId() const noexcept { return id_; }

}  // namespace vx::ogl
