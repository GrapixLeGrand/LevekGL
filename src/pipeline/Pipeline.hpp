#pragma once

#include "../texture/PixelBuffer.hpp"
#include "../texture/Texture.hpp"
#include "../texture/RenderBuffer.hpp"
#include "../buffer/FrameBuffer.hpp"
#include "RenderingPass.hpp"
#include "PipelineRegistry.hpp"

#include <vector>

namespace Levek {

class Pipeline {
private:
    PipelineRegistry* registry = nullptr;
    std::vector<RenderingPass*> passes;
public:
    Pipeline(PipelineRegistry* registryarg, std::vector<RenderingPass*>& passesarg): passes(passesarg), registry(registryarg) {};
    void render();
    void renderFrom(int i);
    void renderUntil(int i);
};

}