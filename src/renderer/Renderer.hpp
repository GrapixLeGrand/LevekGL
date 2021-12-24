#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <stdio.h>

#include "../buffer/IndexBuffer.hpp"
#include "../buffer/VertexArray.hpp"
#include "../buffer/FrameBuffer.hpp"
#include "../shader/Shader.hpp"
#include "../shader/ShaderFactory.hpp"
#include "glm/glm.hpp"

namespace Levek {

enum ClearBits {
    DEPTH = GL_DEPTH_BUFFER_BIT,
    COLOR = GL_COLOR_BUFFER_BIT
};

#define C_STR_CONC(A, B) (std::string(A) + std::string(B))

class Renderer {
private:

    const static std::string quadVertexShader;
    const static std::string quadFragmentShader;

    //points (vertex + tex) of a quad with indices
    const float points[16] = {
        -0.5f,  -0.5f,  0.0f,   0.0f,
        0.5f,   -0.5f,  1.0f,   0.0f,
        0.5f,   0.5f,   1.0f,   1.0f,
        -0.5f,  0.5f,   0.0f,   1.0f
    };

    const unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray quadVertexArray;
    IndexBuffer quadIndexes = IndexBuffer(indices, 6);
    Shader* quadToScreenShader = ShaderFactory::makeFromSource(quadVertexShader, quadFragmentShader); //= ShaderFactory::makeFromSource(quadVertexShader, quadFragmentShader);
    
    /*
    Shader(
        RESOURCES_DIRECTORY"/shaders/Quad.vert",
        RESOURCES_DIRECTORY"/shaders/Quad.frag"
    );*/

    unsigned int clearFlags;
    glm::vec4 clearColor;
    int width;
    int height;

public:

    Renderer(int width, int height)
        : clearFlags(0), clearColor({0, 0, 0, 0}), width(width), height(height) {
        VertexBuffer quadVertexBuffer = VertexBuffer(points, 16 * sizeof(float));
        VertexBufferLayout layout = VertexBufferLayout();
        layout.push<glm::vec2>(2);
        quadVertexArray.addBuffer(quadVertexBuffer, layout);
        quadIndexes.unbind();
        quadVertexArray.unbind();
        quadVertexArray.unbind();
    }

    void setClearColor(glm::vec4 color);
    void setClearFlags(unsigned int flags);
    void setClearFlags(ClearBits flags);
    void clear() const;

    void clear(const FrameBuffer& frameBuffer) const {
        frameBuffer.bind();
        //TODO tomorrow : create functions in the framebuffer that allows clearing data
        /*glClearBufferfi(frameBuffer.getId(), GLint drawbuffer,
  	    GLfloat depth,
  	    GLint stencil);*/
    }

    /**
     * Draw the content of the buffers with the given shader on the default framebuffer.
     * @param va : vertex array
     * @param ib : index buffer
     * @param shader : the shader object
     */
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    
    void draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;

    /**
     * Draw the content of the buffers with the given shader on the default framebuffer.
     * @param va : vertex array
     * @param shader : the shader object
     */
    void draw(const VertexArray& va, const Shader& shader) const;

    /**
     * Draw a texture to the default frame buffer
    */
    void draw(const Texture& texture) const;

    /**
     * Draw the content of the buffers with the given shader on the given framebuffer.
     * @param frameBuffer : framebuffer on which the result will be drawn.
     * @param va : vertex array
     * @param ib : index buffer
     * @param shader : the shader object
     */
    void draw(const FrameBuffer& frameBuffer, const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    
    //will need to remove these ones later
    //void draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;
    void draw(const FrameBuffer* frameBuffer, const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;
    void drawInstances(const VertexArray* va, const IndexBuffer* ib, const Shader* shader, unsigned int instances) const;

};
};
