#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

namespace vx::ogl {

class ShaderCompilationException : public std::runtime_error {
public:
    explicit ShaderCompilationException(const std::string& what_arg) : std::runtime_error(what_arg) {}
};

enum class ShaderType : std::uint32_t { kVertex = 0x8B31, kFragment = 0x8B30, kGeometry = 0x8DD9 };

class Shader {
public:
    explicit Shader(ShaderType type);
    Shader(ShaderType type, const std::string& source);

    ~Shader();

    Shader(const Shader&)            = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void SetSource(const std::string& source) const noexcept;
    void Compile() const;

    [[nodiscard]] std::uint32_t GetId() const noexcept;

private:
    std::uint32_t id_ {};

    void Release() noexcept;
    [[nodiscard]] std::string GetInfoLog() const noexcept;
};

}  // namespace vx::ogl