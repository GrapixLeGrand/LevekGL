#pragma once
#include <cstdint>
#include "../buffer/FrameBufferProperties.hpp"

namespace Levek {

enum PixelBufferType {
    RENDERBUFFER = 0,
    TEXTURE = 1
};

class PixelBuffer {
    uint32_t id;
    PixelBufferType type;
public:
    uint32_t getId() const { return id; }
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void attachToFrameBuffer(FrameBufferProperties::AttachementType type, int index = 0) const = 0;
protected:
    //friend class FrameBuffer;
    PixelBuffer(PixelBufferType argType) : type(argType) {}
    void setId(uint32_t argId) { id = argId; }
};

}