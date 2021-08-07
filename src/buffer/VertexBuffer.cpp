
#include "VertexBuffer.hpp"
#include "../OpenGLError.hpp"
#include "../renderer/Renderer.hpp"

namespace Levek {

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int usage) : size(size), usage(usage) {
    GL_CHECK(glGenBuffers(1, &rendererID)); //generating vb0
    //GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, rendererID)); //binding...
    bind();
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    //unbind();
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size) : VertexBuffer(data, size, GL_STATIC_DRAW) {}


VertexBuffer::~VertexBuffer() {
    GL_CHECK(glDeleteBuffers(1, &rendererID)); //1 for 1 buffer
}

void VertexBuffer::Update(const void* data, unsigned int size) {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    if (this->size == size) {
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
    } else {
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    }
}

void VertexBuffer::bind() const {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, rendererID)); //binding...
}

void VertexBuffer::unbind() const {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
}