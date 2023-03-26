#include "ogl/shader_program.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <utility>

namespace vx::ogl {

ShaderProgram::ShaderProgram() { id_ = glCreateProgram(); }

ShaderProgram::ShaderProgram(const Shader& vertex) {
    id_ = glCreateProgram();
    Attach(vertex);
    Link();
}

ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment) {
    id_ = glCreateProgram();
    Attach(vertex);
    Attach(fragment);
    Link();
}

ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment, const Shader& geometry) {
    id_ = glCreateProgram();
    Attach(vertex);
    Attach(fragment);
    Attach(geometry);
    Link();
}

ShaderProgram::~ShaderProgram() { Release(); }

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
    : id_(other.id_), uniformLocations_(std::move(other.uniformLocations_)) {
    other.id_ = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
    if (this != &other) {
        Release();

        std::swap(id_, other.id_);
        std::swap(uniformLocations_, other.uniformLocations_);
    }

    return *this;
}

void ShaderProgram::Attach(const Shader& shader) const noexcept { glAttachShader(id_, shader.GetId()); }

void ShaderProgram::Link() const {
    glLinkProgram(id_);

    GLint link_status;
    glGetProgramiv(id_, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        throw ShaderLinkingException {GetInfoLog()};
    }
}

void ShaderProgram::Use() const noexcept { glUseProgram(id_); }

UniformLocation ShaderProgram::GetUniformLocation(const std::string& name) noexcept {
    if (!uniformLocations_.contains(name)) {
        uniformLocations_[name] = glGetUniformLocation(id_, name.c_str());
    }
    return uniformLocations_[name];
}

void ShaderProgram::SetUniformFloat(const std::string& name, const float value) noexcept {
    Use();
    glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniformFloatArray(const std::string& name, const std::span<float>& array) noexcept {
    Use();
    glUniform1fv(GetUniformLocation(name), array.size(), array.data());
}

void ShaderProgram::SetUniformVector2(const std::string& name, const glm::vec2& vector) noexcept {
    Use();
    glUniform2f(GetUniformLocation(name), vector.x, vector.y);
}

void ShaderProgram::SetUniformVector3(const std::string& name, const glm::vec3& vector) noexcept {
    Use();
    glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void ShaderProgram::SetUniformVector4(const std::string& name, const glm::vec4& vector) noexcept {
    Use();
    glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::SetUniformMatrix4(const std::string& name, const glm::mat4& matrix) noexcept {
    Use();
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetUniformInteger(const std::string& name, const std::int32_t value) noexcept {
    Use();
    glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniformIntegerArray(const std::string& name, const std::span<std::int32_t>& array) noexcept {
    Use();
    glUniform1iv(GetUniformLocation(name), array.size(), array.data());
}

void ShaderProgram::Release() noexcept {
    glDeleteProgram(id_);
    id_ = 0;
}
std::string ShaderProgram::GetInfoLog() const noexcept {
    GLint length;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &length);

    if (length > 0) {
        std::string info_log(length, 0);
        glGetProgramInfoLog(id_, length, &length, info_log.data());
        return info_log;
    }

    return {};
}

}  // namespace vx::ogl
