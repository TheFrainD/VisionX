#include "ogl/vertex_array.h"

#include <glad/glad.h>

#include <utility>

namespace vx::ogl {

VertexArray::VertexArray() { glGenVertexArrays(1, &id_); }

VertexArray::~VertexArray() { Release(); }

VertexArray::VertexArray(VertexArray&& other) noexcept : id_(other.id_) { other.id_ = 0; }

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
    if (this != &other) {
        Release();

        std::swap(id_, other.id_);
    }

    return *this;
}

void VertexArray::Bind() const noexcept { glBindVertexArray(id_); }

void VertexArray::Unbind() noexcept { glBindVertexArray(0); }

void VertexArray::SetElementBuffer(const VertexBuffer& buffer) const noexcept {
    Bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.GetId());
}

void VertexArray::BindAttribute(const VertexBuffer& buffer, const std::uint32_t index, const std::int32_t size,
                                const DataType type, const std::int32_t stride,
                                const std::int32_t offset) const noexcept {
    Bind();
    buffer.Bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, static_cast<GLenum>(type), GL_FALSE, stride,
                          reinterpret_cast<const void*>(offset));
}

void VertexArray::Release() noexcept {
    if (id_ != 0) {
        glDeleteVertexArrays(1, &id_);
        id_ = 0;
    }
}

}  // namespace vx::ogl