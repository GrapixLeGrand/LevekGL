#include <iostream>
#include "Renderer.hpp"
#include "../OpenGLError.hpp"

namespace Levek {

const std::string Renderer::quadVertexShader = 
    "#version 430 core\n"
    "//Quad vert\n"
    "layout (location = 0) in vec2 aPos;"
    "layout (location = 1) in vec2 aTexCoords;"

    "out vec2 TexCoords;"

    "void main()"
    "{"
        "gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);"
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
        "FragColor = texture(screenTexture, TexCoords);"
    "}";

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

void Renderer::draw(const VertexArray& va, const Shader& shader) const {
    glViewport(0, 0, width, height);
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //set the default framebuffer 
    shader.bind();
    va.bind();
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3)); /* WARNING just for now !!! */
}

void Renderer::draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const {

    glViewport(0, 0, width, height);
    shader->bind();
    va->bind();
    ib->bind();
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));   
    GL_CHECK(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
    //GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 36));
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
