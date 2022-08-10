#pragma once

#include <unordered_set>
#include "../texture/Texture.hpp"
#include "../texture/RenderBuffer.hpp"
#include "glm/glm.hpp"
#include "../buffer/FrameBufferProperties.hpp"


namespace Levek {

enum AttachmentType {
    COLOR_ATTACHMENT,
    DEPTH_ATTACHMENT,
    DEPTH_STENCIL_ATTACHMENT
};
/*
enum ColorAttachmentSlot {
    SLOT_0 = GL_COLOR_ATTACHMENT0,
    SLOT_1 = GL_COLOR_ATTACHMENT1,
    SLOT_2 = GL_COLOR_ATTACHMENT2,
    SLOT_3 = GL_COLOR_ATTACHMENT3
};*/

//#define LEVEKGL_MAX_COLOR_ATTACHMENT_SLOTS 16
//extern const int COLOR_ATTACHMENT_SLOTS[MAX_COLOR_ATTACHMENT_SLOTS];

/**
 * We can attach textures or/and renderbuffers to a framebuffer.
 * They are the same but renderbuffer are write only. Current implementation
 * supports up to 4 color attachments.
 */
class FrameBuffer {
private:

    const static int MAX_COLOR_ATTACHMENT_SLOTS = 16;
    const static int COLOR_ATTACHMENT_SLOTS[MAX_COLOR_ATTACHMENT_SLOTS];
    
    unsigned int id;
    int width = 0;
    int height = 0;
    bool complete = false;


    bool finalized;
    //how many color attachments are expected, default is 1
    int expectedColorAttachments    = 1;
    int currentColorAttachments     = 0;

    //these two are mutually exclusive
    bool hasColor         = false;
    bool hasDepth         = false;  //at most 1
    bool hasDepthStencil  = false;  //at most 1

    glm::vec4 clearColor {0.0f, 0.0f, 0.0f, 0.0f};
    float clearDepth = 1.0f;
    unsigned int clearStencil = 0;
    unsigned int clearBits = 0;

    void checkIfComplete();
public:

    FrameBuffer();

    /**
     * Instanciate a framebuffer with 1 color attachment (default)
     * @param width
     * @param height
     * @param colorAttachments
     */
    FrameBuffer(int width, int height);

    /**
     * Instanciate a framebuffer by specifying the number
     * of color attachments that will be present.
     * @param width
     * @param height
     * @param colorAttachments
     */
    FrameBuffer(int width, int height, int colorAttachments);

    ~FrameBuffer();
    
    void addColorAttachment(const PixelBuffer* buffer, int index);

    void addAttachment(const PixelBuffer* buffer, FrameBufferProperties::AttachementType type);

    //TODO
    void removeAttachment(const PixelBuffer* buffer);

    /**
     * Add a color attachment. If more than 1 color attchment is
     * expected, this attachment will allways refer to channel 1.
     * @param texture : the texture that will be attached to the
     * FrameBuffer
     */
    void addColorAttachment(const Texture& texture);

    /**
     * Add a color attachment
     * @param renderBuffer : the RenderBuffer that will be attached
     * as color attachment
     */
    void addColorAttachment(const RenderBuffer& renderBuffer);

    /**
     * Add a color attachment. Allows to specify the channel index
     * of the color attachment.
     * @param texture : the texture that will be attached to the
     * FrameBuffer at some index
     * @param index : the index of the color attachment
     */
    void addColorAttachment(const Texture& texture, int index);

    /**
     * Attach a depth buffer to the FrameBuffer.
     * @param texture : the single channel Texture of type Depth.
     */
    void addDepthAttachment(const Texture& texture);

    /**
     * Attach a depth buffer to the FrameBuffer.
     * @param renderBuffer : the single channel RenderBuffer of type Depth.
     */
    void addDepthAttachment(const RenderBuffer& renderBuffer);

    /**
     * attach a stencil buffer to the FrameBuffer
     * @param renderBuffer : the Texture of type depth stencil
     */
    void addDepthStencilAttachment(const Texture& texture);

    /**
     * attach a stencil buffer to the FrameBuffer
     * @param renderBuffer : the single channel RenderBuffer of type depth stencil
     */
    void addDepthStencilAttachment(const RenderBuffer& renderBuffer);

    //we throw away these
    //void attachTexture(const Texture& texture, AttachmentType type);
    //void attachRenderBuffer(const RenderBuffer& texture, AttachmentType type);

    void clear() const;
    void finalize();
    void bind() const;
    void unbind() const;

    unsigned int getId() const { return id; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    /**
     * @brief The number of color attachment
     * 
     * @return int 
     */
    int hasColorAttachment() const {
        return currentColorAttachments;
    }

    /**
     * @brief true iff a depth attachment is present
     * 
     * @return true 
     * @return false 
     */
    bool hasDepthAttachment() const {
        return hasDepth;
    }

    /**
     * @brief true iff a depth stencil attachment is present
     * 
     * @return true 
     * @return false 
     */
    bool hasDepthStencilAttachment() const {
        return hasDepthStencil;
    }

};
};