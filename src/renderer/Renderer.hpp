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

/*
Back for back faces and front for front faces
*/
enum CullFaceMode {
    DEFAULT = GL_BACK,
    BACK = GL_BACK,
    FRONT = GL_FRONT
};

#define C_STR_CONC(A, B) (std::string(A) + std::string(B))

class Renderer {
private:

    const static std::string quadVertexShader;
    const static std::string quadFragmentShader;

    //points (vertex + tex) of a quad with indices
    const float points[16] = {
        -1.0f,  -1.0f,   0.0f,   0.0f,
        1.0f,   -1.0f,   1.0f,   0.0f,
        1.0f,   1.0f,   1.0f,   1.0f,
        -1.0f,   1.0f,   0.0f,   1.0f
    };

    /*
    const float points[16] = {
        -0.5f,  -0.5f,  0.0f,   0.0f,
        0.5f,   -0.5f,  1.0f,   0.0f,
        0.5f,   0.5f,   1.0f,   1.0f,
        -0.5f,  0.5f,   0.0f,   1.0f
    };*/

    const unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray quadVertexArray;
    IndexBuffer quadIndexes = IndexBuffer(indices, 6);
    Shader quadToScreenShader = ShaderFactory::makeFromSource(quadVertexShader, quadFragmentShader); //= ShaderFactory::makeFromSource(quadVertexShader, quadFragmentShader);
    const glm::vec2 defaultQuadToScreenOffset = glm::vec2(0.0f);
    const glm::vec2 defaultQuadToScreenScale = glm::vec2(1.0f);

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

        //creating rendering objects for the quad that can be rendered on the screen
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

    void setDepthMask(bool mask) const {
        if (mask) {
            GL_CHECK(glDepthMask(GL_TRUE));
        } else {
            GL_CHECK(glDepthMask(GL_FALSE));
        } 
    }

    void setCullFaceMode(CullFaceMode mode) const {
        GL_CHECK(glCullFace(mode));
    }

    void clear(const FrameBuffer& frameBuffer) const {

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
     * Draw a texture to the default frame buffer at the specified position
    */
    void draw(const Texture& texture, const glm::vec2& position) const;

    /**
     * @brief draw a texture on the main framebuffer by specifying the scale and the position
     * the center of the screen is (0, 0) and the bounds on each axis are [-1, 1].
     * 
     * @param texture 
     * @param scale 
     * @param position 
     */
    void draw(const Texture& texture, const glm::vec2& position, const glm::vec2& scale) const;

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
