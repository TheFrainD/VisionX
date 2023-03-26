#include "ogl/vertex_buffer.h"

#include <glad/glad.h>

#include <utility>

namespace vx::ogl {

VertexBuffer::VertexBuffer(const void *data, const std::size_t size, const BufferUsage usage) : size_(size) {
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size_, data, static_cast<GLenum>(usage));
}

VertexBuffer::~VertexBuffer() { Release(); }

VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept : id_(other.id_), size_(other.size_) { other.id_ = 0; }

VertexBuffer &VertexBuffer::operator=(VertexBuffer &&other) noexcept {
    if (this != &other) {
        Release();

        std::swap(id_, other.id_);
        std::swap(size_, other.size_);
    }

    return *this;
}
void VertexBuffer::Bind() const noexcept { glBindBuffer(GL_ARRAY_BUFFER, id_); }

void VertexBuffer::Unbind() noexcept { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::SetData(const void *data, const std::size_t size) noexcept {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    size_ = size;
    glBufferData(GL_ARRAY_BUFFER, size_, data, GL_DYNAMIC_DRAW);
}

void VertexBuffer::SubData(const void *data, const std::size_t offset, const std::size_t size) noexcept {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    size_ = size;
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::Release() noexcept {
    glDeleteBuffers(1, &id_);
    id_ = 0;
}

}  // namespace vx::ogl
