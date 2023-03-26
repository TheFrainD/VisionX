#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <span>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "ogl/shader.h"

namespace vx::ogl {

class ShaderLinkingException : public std::runtime_error {
public:
    explicit ShaderLinkingException(const std::string& what_arg) : std::runtime_error(what_arg) {}
};

using UniformLocation = std::int32_t;

class ShaderProgram {
public:
    ShaderProgram();
    explicit ShaderProgram(const Shader& vertex);
    ShaderProgram(const Shader& vertex, const Shader& fragment);
    ShaderProgram(const Shader& vertex, const Shader& fragment, const Shader& geometry);

    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&)            = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    void Attach(const Shader& shader) const noexcept;
    void Link() const;
    void Use() const noexcept;

    [[nodiscard]] UniformLocation GetUniformLocation(const std::string& name) noexcept;

    void SetUniformFloat(const std::string& name, float value) noexcept;
    void SetUniformFloatArray(const std::string& name, const std::span<float>& array) noexcept;
    void SetUniformVector2(const std::string& name, const glm::vec2& vector) noexcept;
    void SetUniformVector3(const std::string& name, const glm::vec3& vector) noexcept;
    void SetUniformVector4(const std::string& name, const glm::vec4& vector) noexcept;
    void SetUniformMatrix4(const std::string& name, const glm::mat4& matrix) noexcept;
    void SetUniformInteger(const std::string& name, std::int32_t value) noexcept;
    void SetUniformIntegerArray(const std::string& name, const std::span<std::int32_t>& array) noexcept;

private:
    std::uint32_t id_ {};
    std::unordered_map<std::string, UniformLocation> uniformLocations_;

    void Release() noexcept;
    [[nodiscard]] std::string GetInfoLog() const noexcept;
};

}  // namespace vx::ogl