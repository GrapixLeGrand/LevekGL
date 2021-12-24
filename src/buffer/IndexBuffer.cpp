
#include "IndexBuffer.hpp"
#include "../renderer/Renderer.hpp"

namespace Levek {

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

void IndexBuffer::bind() const {
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID)); //binding...
}

void IndexBuffer::unbind() const {
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
} //Levek