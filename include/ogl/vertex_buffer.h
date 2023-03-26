#pragma once

#include <cstddef>
#include <cstdint>

namespace vx::ogl {

enum class BufferUsage : std::uint32_t {
    kStreamDraw  = 0x88E0,
    kStreamRead  = 0x88E1,
    kStreamCopy  = 0x88E2,
    kStaticDraw  = 0x88E4,
    kStaticRead  = 0x88E5,
    kStaticCopy  = 0x88E6,
    kDynamicDraw = 0x88E8,
    kDynamicRead = 0x88E9,
    kDynamicCopy = 0x88EA
};

class VertexBuffer {
public:
    VertexBuffer(const void* data, std::size_t size, BufferUsage usage);

    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&)            = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void Bind() const noexcept;
    static void Unbind() noexcept;

    void SetData(const void* data, std::size_t size) noexcept;
    void SubData(const void* data, std::size_t offset, std::size_t size) noexcept;

private:
    std::uint32_t id_ {};
    std::size_t size_;

    void Release() noexcept;
};

}  // namespace vx::ogl