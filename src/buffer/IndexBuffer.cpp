
#include "IndexBuffer.hpp"
#include "../OpenGLError.hpp"
#include <GL/glew.h>
#include "../renderer/Renderer.hpp"

namespace Levek {

IndexBuffer::IndexBuffer() {
    GL_CHECK(glGenBuffers(1, &rendererID));
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
   : count(count) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    GL_CHECK(glGenBuffers(1, &rendererID)); //generating vb0
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID)); //binding...
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW)); //array buffer == buffer with vertex attribute
    unbind();
}

IndexBuffer::IndexBuffer(const Mesh* mesh): IndexBuffer(mesh->getIndices().data(), mesh->getIndices().size()) {}

IndexBuffer::~IndexBuffer() {
    GL_CHECK(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::update(const Mesh* mesh) {
    bind();
    auto& indices = mesh->getIndices();
    this->count = indices.size();
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
}

void IndexBuffer::update(const unsigned int* data, unsigned int count) {
    bind();
    this->count = count;
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::bind() const {
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID)); //binding...
}

void IndexBuffer::unbind() const {
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
} //Levek