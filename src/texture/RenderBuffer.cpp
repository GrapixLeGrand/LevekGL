#include "RenderBuffer.hpp"

#include "../OpenGLError.hpp"
//#include "../renderer/Renderer.h"
#include <GL/glew.h>
#include <cassert>

namespace Levek {

RenderBuffer::RenderBuffer() {
    GL_CHECK(glGenRenderbuffers(1, &id));
}


RenderBuffer::RenderBuffer(int width, int height, TextureParameters::TextureType type)
 : id(0), width(width), height(height), type(type) {
    assert(width > 0 && height > 0);
    assert(type != TextureParameters::RGBA);
    GL_CHECK(glGenRenderbuffers(1, &id));
    bind();
    update(width, height, type);
}

void RenderBuffer::update(int w, int h, TextureParameters::TextureType type) {
    bind();
    this->width = width;
    this->height = height;
    this->type = type;
    //warning not so sure with the types
    switch (type) {
        case TextureParameters::RGB:
        GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, width, height));
        break;
        case TextureParameters::DEPTH:
        GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height));
        break;
        case TextureParameters::DEPTH_STENCIL:
        GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
        break;
        default:
            assert(false);
        break;
    }
}

RenderBuffer::~RenderBuffer() {
    bind();
    GL_CHECK(glDeleteRenderbuffers(1, &id));
}

void RenderBuffer::bind() const {
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, id));
}

void RenderBuffer::unbind() const {
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}


};