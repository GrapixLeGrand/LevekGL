
#include "FrameBuffer.hpp"
#include "../OpenGLError.hpp"
//#include "../renderer/Renderer.h"
#include <GL/glew.h>
#include <cassert>

namespace Levek {

const int FrameBuffer::COLOR_ATTACHMENT_SLOTS[FrameBuffer::MAX_COLOR_ATTACHMENT_SLOTS]  = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3,
        GL_COLOR_ATTACHMENT4,
        GL_COLOR_ATTACHMENT5,
        GL_COLOR_ATTACHMENT6,
        GL_COLOR_ATTACHMENT7,
        GL_COLOR_ATTACHMENT8,
        GL_COLOR_ATTACHMENT9,
        GL_COLOR_ATTACHMENT10,
        GL_COLOR_ATTACHMENT11,
        GL_COLOR_ATTACHMENT12,
        GL_COLOR_ATTACHMENT13,
        GL_COLOR_ATTACHMENT14,
        GL_COLOR_ATTACHMENT15
};

FrameBuffer::FrameBuffer(): id(0), width(0), height(0) {
    GL_CHECK(glGenFramebuffers(1, &id));
}

//TODO remove
FrameBuffer::FrameBuffer(int width, int height):
    id(0),
    width(width), height(height),
    finalized(false), 
    expectedColorAttachments(1) /* by default a single color attachment */
{
    LEVEK_RENDERING_ASSERT_(width > 0);
    LEVEK_RENDERING_ASSERT_(height > 0);
    GL_CHECK(glGenFramebuffers(1, &id));
}

//TODO remove
FrameBuffer::FrameBuffer(int width, int height, int colorAttachments):
    id(0),
    width(width), height(height),
    finalized(false),
    expectedColorAttachments(colorAttachments),
    hasColor(colorAttachments > 0 ? true : false)
{   
    LEVEK_RENDERING_ASSERT_(colorAttachments >= 0);
    LEVEK_RENDERING_ASSERT_(width > 0);
    LEVEK_RENDERING_ASSERT_(height > 0);
    GL_CHECK(glGenFramebuffers(1, &id));
}

FrameBuffer::~FrameBuffer() {
   bind();
   GL_CHECK(glDeleteFramebuffers(1, &id));  
}

void FrameBuffer::bind() const {
    //LEVEK_RENDERING_ASSERT(finalized, "forbidden to use bind() non-finalized FrameBuffer");
    if (!complete) { LEVEK_WARNING("framebuffer with id %d is being bounded but is incomplete\n", id); }
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
}

void FrameBuffer::unbind() const {
    //LEVEK_RENDERING_ASSERT(finalized, "forbidden to use unbind() on non-finalized FrameBuffer");
    if (!complete) { LEVEK_WARNING("framebuffer with id %d is being bounded but is incomplete\n", id); }
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

//void addColorAttachment(const PixelBuffer* buffer);


void FrameBuffer::checkIfComplete() {
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER); // == GL_FRAMEBUFFER_COMPLETE;
    switch (status) {
        case GL_FRAMEBUFFER_COMPLETE:
            complete = true;
            LEVEK_MESSAGE("framebuffer with id %d is completed and usable\n", id);
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            LEVEK_MESSAGE("framebuffer with id %d is incomplete or missing attachments (code %d)\n", id, status);
        break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            LEVEK_ERROR("framebuffer with id %d has uncompatible attachments\n", id);
        default:
            LEVEK_WARNING("framebuffer with id %d was checked but the result is unknown %d\n", id, status);
    }
}

/**
 * Assert macro to reduce boiler plate code.
 */
#define ATTACHMENT_BASIC_ASSERTS(BUFFER_NAME) \
    LEVEK_RENDERING_ASSERT(!finalized, \
        "All call to attachments functions after object finalization are forbidden"); \
    LEVEK_RENDERING_ASSERT(BUFFER_NAME.getWidth() == width && BUFFER_NAME.getHeight() == height, \
        "the dimensions of the attachment must match those of the FrameBuffer");

void FrameBuffer::addColorAttachment(const PixelBuffer* buffer, int index) {
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    buffer->bind();
    buffer->attachToFrameBuffer(FrameBufferProperties::AttachementType::COLOR, index);
    checkIfComplete();
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    buffer->unbind();
}

void FrameBuffer::addAttachment(const PixelBuffer* buffer, FrameBufferProperties::AttachementType type) {
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    buffer->bind();
    buffer->attachToFrameBuffer(type);
    checkIfComplete();
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    buffer->unbind();
}

void FrameBuffer::addColorAttachment(const Texture& texture) {
    ATTACHMENT_BASIC_ASSERTS(texture);
    LEVEK_RENDERING_ASSERT(
        currentColorAttachments < expectedColorAttachments, 
        "trying to add more color attachment that allowed"
    );
    LEVEK_RENDERING_ASSERT(
        texture.getType() == TextureParameters::RGBA || texture.getType() == TextureParameters::RGB,
        "Texture Color attachment must have RGBA_8 or RGB_8 type"
    );

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    texture.bind();
    currentColorAttachments++;
    GL_CHECK(
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getId(), 0);
    )
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    texture.unbind();
}

void FrameBuffer::addColorAttachment(const RenderBuffer& buffer) {
    ATTACHMENT_BASIC_ASSERTS(buffer);
    LEVEK_RENDERING_ASSERT(
        currentColorAttachments < expectedColorAttachments, 
        "trying to add more color attachment that expected"
    );
    LEVEK_RENDERING_ASSERT(
        buffer.getType() == TextureParameters::RGBA || buffer.getType() == TextureParameters::RGB, 
        "Texture Color attachment must have RGBA_8 or RGB_8 type"
    );

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    buffer.bind();
    currentColorAttachments++;
    GL_CHECK(
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer.getId(), 0);
    )
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    buffer.unbind();
        
}

void FrameBuffer::addColorAttachment(const Texture& texture, int index) {
    ATTACHMENT_BASIC_ASSERTS(texture);
    LEVEK_RENDERING_ASSERT(
        currentColorAttachments < expectedColorAttachments, 
        "trying to add more color attachment that expected"
    );
    LEVEK_RENDERING_ASSERT(
        texture.getType() == TextureParameters::RGBA || texture.getType() == TextureParameters::RGB, 
        "Texture Color attachment must have RGBA_8 or RGB_8 type"
    );
    LEVEK_RENDERING_ASSERT(index > 0 && index < MAX_COLOR_ATTACHMENT_SLOTS, "index out of bounds");
    
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    texture.bind();
    currentColorAttachments++;
    GL_CHECK(
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, texture.getId(), 0);
    )
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    texture.unbind();

}

void FrameBuffer::addDepthAttachment(const Texture& texture) {
    ATTACHMENT_BASIC_ASSERTS(texture);
    LEVEK_RENDERING_ASSERT(
        texture.getType() == TextureParameters::DEPTH,
        "Texture Depth attachment must have DEPTH_24 type"
    );
    LEVEK_RENDERING_ASSERT(
        !hasDepthStencil,
        "cannot have depth attachment as well as depth stencil attachment"
    );
    
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    texture.bind();
    hasDepth = true;
    GL_CHECK(
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.getId(), 0);
    );
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    texture.unbind();
}

void FrameBuffer::addDepthAttachment(const RenderBuffer& buffer) {
    ATTACHMENT_BASIC_ASSERTS(buffer);
    LEVEK_RENDERING_ASSERT(
        buffer.getType() == TextureParameters::DEPTH,
        "RenderBuffer Depth attachment must have DEPTH_24 type"
    );
    LEVEK_RENDERING_ASSERT(
        !hasDepthStencil,
        "cannot have depth attachment as well as depth stencil attachment"
    );
    
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    buffer.bind();
    hasDepth = true;
    GL_CHECK(
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer.getId());
    )
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    buffer.unbind();
}

void FrameBuffer::addDepthStencilAttachment(const Texture& texture) {
    ATTACHMENT_BASIC_ASSERTS(texture);
    LEVEK_RENDERING_ASSERT(
        texture.getType() == TextureParameters::DEPTH_STENCIL,
        "Texture depth stencil attachment must have DEPTH_24 type"
    );
    LEVEK_RENDERING_ASSERT(
        !hasDepth,
        "cannot have depth attachment as well as depth stencil attachment"
    );
    
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    texture.bind();
    hasDepthStencil = true;
    GL_CHECK(
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.getId(), 0);
    )
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    texture.unbind();
}

void FrameBuffer::addDepthStencilAttachment(const RenderBuffer& buffer) {
    ATTACHMENT_BASIC_ASSERTS(buffer);
    LEVEK_RENDERING_ASSERT(buffer.getType() == TextureParameters::DEPTH_STENCIL,
        "RenderBuffer Depth stencil attachment must have DEPTH_24 type");
    LEVEK_RENDERING_ASSERT(
        !hasDepth,
        "cannot have depth attachment as well as depth stencil attachment"
    );
    buffer.bind();
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
    hasDepthStencil = true;
    GL_CHECK(
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer.getId());
    )
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    buffer.unbind();
}   

void FrameBuffer::finalize() {
    LEVEK_RENDERING_ASSERT(!finalized, "framebuffer already finalized");
    LEVEK_RENDERING_ASSERT(
        (hasDepth && !hasDepthStencil) || (!hasDepth && hasDepthStencil),
        "cannot attach depth and depth stencil attachment"
    );
    finalized = true;

    if (hasDepth) {
        clearBits |= GL_DEPTH_BUFFER_BIT;
        GL_CHECK(glClearDepth(clearDepth));
    }

    if (hasDepthStencil) {
        clearBits |= GL_STENCIL_BUFFER_BIT;
        GL_CHECK(glClearStencil(clearStencil));
    }

    if (hasColor) {
        clearBits |= GL_COLOR_BUFFER_BIT;
        GL_CHECK(glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a));
    }

    bind();
    if (!hasColor) {
        GL_CHECK(glDrawBuffer(GL_NONE));
        GL_CHECK(glReadBuffer(GL_NONE));
    }
    GL_CHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

void FrameBuffer::clear() const {
    bind();
    GL_CHECK(glClear(clearBits));
}

};