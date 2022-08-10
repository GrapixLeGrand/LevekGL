#pragma once

#include <vector>
#include "../buffer/FrameBuffer.hpp"

namespace Levek {
class RenderingPass {
protected:
    FrameBuffer* inputFb = nullptr;
    FrameBuffer* outputFb = nullptr;
    RenderingPass(FrameBuffer* in, FrameBuffer* out): inputFb(in), outputFb(out) {};
    virtual ~RenderingPass() = 0;
public:
    FrameBuffer* getOutputFramebuffer() { return outputFb; }
    virtual void render() = 0;
};
}