#include <iostream>
#include "Renderer.hpp"
#include "../OpenGLError.hpp"
#include <GL/glew.h>

namespace Levek {

const std::string Renderer::quadVertexShader = 
    "#version 430 core\n"
    "//Quad vert\n"
    "layout (location = 0) in vec2 aPos;"
    "layout (location = 1) in vec2 aTexCoords;"

    "out vec2 TexCoords;"
    
    "uniform vec2 position;"
    "uniform vec2 scale;"

    "void main()"
    "{"
        "gl_Position = vec4(scale.x * (aPos.x + position.x), scale.y * (aPos.y + position.y), 0.0, 1.0);"
        "TexCoords = aTexCoords;"
    "}";

const std::string Renderer::quadFragmentShader = 
    "#version 430 core\n"
    "//Quad frag\n"
    "out vec4 FragColor;"
    
    "in vec2 TexCoords;"

    "uniform sampler2D screenTexture;"

    "void main()"
    "{"
        "FragColor = vec4(texture(screenTexture, TexCoords));"
    "}";


Renderer::Renderer(int width, int height)
    : clearFlags(0), clearColor({ 0, 0, 0, 0 }), width(width), height(height) {

    //creating rendering objects for the quad that can be rendered on the screen
    VertexBuffer quadVertexBuffer = VertexBuffer(points, 16 * sizeof(float));
    VertexBufferLayout layout = VertexBufferLayout();
    layout.push<glm::vec2>(2);
    quadVertexArray.addBuffer(quadVertexBuffer, layout);
    quadIndexes.unbind();
    quadVertexArray.unbind();
    quadVertexArray.unbind();
}


void Renderer::setDepthMask(bool mask) const {
    if (mask) {
        GL_CHECK(glDepthMask(GL_TRUE));
    }
    else {
        GL_CHECK(glDepthMask(GL_FALSE));
    }
}


void Renderer::setCullFaceMode(CullFaceMode mode) const {
    GL_CHECK(glCullFace(mode));
}

void Renderer::clear(const FrameBuffer& frameBuffer) const {

    //for clearing framebuffers but cannot be const :(
    glm::vec4 defaultFrameBufferClearColor = glm::vec4(0.0f);
    float defaultFrameBufferDepth = 1.0f;
    float defaultFrameBufferDepthStencil = 0; //TODO WARNING I'm not sure

    if (frameBuffer.hasColorAttachment() > 0) {
        glClearNamedFramebufferfv(
            frameBuffer.getId(),
            GL_COLOR,
            0,
            &defaultFrameBufferClearColor[0]
        );
    }

    if (frameBuffer.hasDepthAttachment()) {
        glClearNamedFramebufferfv(
            frameBuffer.getId(),
            GL_DEPTH,
            0,
            &defaultFrameBufferDepth
        );
    }

    if (frameBuffer.hasDepthStencilAttachment()) {
        glClearNamedFramebufferfv(
            frameBuffer.getId(),
            GL_DEPTH_STENCIL,
            0,
            &defaultFrameBufferDepthStencil
        );
    }

}

void Renderer::setClearFlags(unsigned int flags) {
    this->clearFlags = flags;
}

void Renderer::setClearFlags(ClearBits bits) {
    this->clearFlags = bits;
}

void Renderer::clear() const {
    GL_CHECK(glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a));
    GL_CHECK(glClear(this->clearFlags));
}


void Renderer::setClearColor(glm::vec4 color) {
    this->clearColor = color;
}

void Renderer::draw(const Texture& texture) const {
    glViewport(0, 0, width, height);
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //set the default framebuffer 
    quadToScreenShader.bind();
    texture.activateAndBind(0);
    quadToScreenShader.setUniform2f("offset", defaultQuadToScreenOffset);
    quadToScreenShader.setUniform1i("screenTexture", 0);
    quadVertexArray.bind();
    quadIndexes.bind();
    GL_CHECK(glDrawElements(GL_TRIANGLES, quadIndexes.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const Texture& texture, const glm::vec2& position) const {

}

void Renderer::draw(const Texture& texture, const glm::vec2& position, const glm::vec2& scale) const {
    glViewport(0, 0, width, height);
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //set the default framebuffer 
    quadToScreenShader.bind();
    texture.activateAndBind(0);
    quadToScreenShader.setUniform2f("position", position / scale);
    quadToScreenShader.setUniform2f("scale", scale);
    quadToScreenShader.setUniform1i("screenTexture", 0);
    quadVertexArray.bind();
    quadIndexes.bind();
    GL_CHECK(glDrawElements(GL_TRIANGLES, quadIndexes.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    glViewport(0, 0, width, height);
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //set the default framebuffer 
    shader.bind();
    va.bind();
    ib.bind();
    GL_CHECK(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const {
    glViewport(0, 0, width, height);
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //set the default framebuffer 
    shader->bind();
    va->bind();
    ib->bind();
    GL_CHECK(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const VertexArray& va, const Shader& shader) const {
    //glViewport(0, 0, width, height);
    //GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //set the default framebuffer 
    shader.bind();
    va.bind();
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, (unsigned int) va.getVerticesNum())); /* WARNING just for now !!! (I think its okay now before was 3?) */
}


void Renderer::draw(const VertexArray* va, const Shader* shader) const {
    //glViewport(0, 0, width, height);
    //GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //set the default framebuffer 
    shader->bind();
    va->bind();
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, (unsigned int) va->getVerticesNum())); /* WARNING just for now !!! (I think its okay now before was 3?) */
}


void Renderer::draw(const FrameBuffer* frameBuffer, const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const {
    glViewport(0, 0, frameBuffer->getWidth(), frameBuffer->getHeight());
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->getId()));
    shader->bind();
    va->bind();
    ib->bind();   
    GL_CHECK(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const FrameBuffer& frameBuffer, const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    glViewport(0, 0, frameBuffer.getWidth(), frameBuffer.getHeight());
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.getId()));
    shader.bind();
    va.bind();
    ib.bind();
    GL_CHECK(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}


void Renderer::drawInstances(const VertexArray* va, const IndexBuffer* ib, const Shader* shader, unsigned int instances) const {
    
    shader->bind();
    va->bind();
    ib->bind();

    GL_CHECK(glDrawElementsInstanced(
        GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, 0, instances
    ));

}



};
