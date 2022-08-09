
#include "VertexBuffer.hpp"
#include "../OpenGLError.hpp"
#include "../renderer/Renderer.hpp"
#include <GL/glew.h>

namespace Levek {


VertexBuffer::VertexBuffer() {
    GL_CHECK(glGenBuffers(1, &rendererID));
}

/**
 * @brief Construct a new Vertex Buffer:: Vertex Buffer object
 * 
 * @param data 
 * @param size the size in bytes
 * @param usage 
 */
VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int usage) : size(size), usage(usage) {
    GL_CHECK(glGenBuffers(1, &rendererID)); //generating vb0
    //GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, rendererID)); //binding...
    bind();
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    //unbind();
}

VertexBuffer::VertexBuffer(const void* data, size_t size): VertexBuffer(data, (unsigned int) size, GL_STATIC_DRAW) {}
VertexBuffer::VertexBuffer(const void* data, unsigned int size): VertexBuffer(data, size, GL_STATIC_DRAW) {}

VertexBuffer::VertexBuffer(const Mesh* mesh): VertexBuffer(mesh->getVertices().data(), mesh->getVerticesBytes()) {}

VertexBuffer::~VertexBuffer() {
    GL_CHECK(glDeleteBuffers(1, &rendererID)); //1 for 1 buffer
}

void VertexBuffer::update(const void* data, unsigned int size) {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    if (this->size >= size) {
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
    } else {
        this->size = size; //NOT SURE
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }
}

void VertexBuffer::bind() const {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, rendererID)); //binding...
}

void VertexBuffer::unbind() const {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
}