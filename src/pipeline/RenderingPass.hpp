#pragma once

#include <vector>
#include "../buffer/FrameBuffer.hpp"
#include "PipelineRegistry.hpp"

namespace Levek {
class RenderingPass {
protected:
    PipelineRegistry* registry = nullptr;
    FrameBuffer fb;
    RenderingPass(PipelineRegistry* registryarg) : registry(registryarg) {};
    //virtual ~RenderingPass() = 0;
public:
    virtual void render() = 0;
};
}