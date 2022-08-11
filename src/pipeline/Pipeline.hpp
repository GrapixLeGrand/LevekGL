#pragma once

#include "../texture/PixelBuffer.hpp"
#include "../texture/Texture.hpp"
#include "../texture/RenderBuffer.hpp"
#include "../buffer/FrameBuffer.hpp"
#include "RenderingPass.hpp"

#include <vector>

namespace Levek {

class Pipeline {
private:
    std::vector<Texture*> textures;
    std::vector<RenderBuffer*> renderBuffers;
    std::vector<FrameBuffer*> frameBuffers;
    
    std::vector<RenderingPass*> renderingPasses;

    FrameBuffer* frame = nullptr;
public:
    void addRenderingPass(RenderingPass* pass);
    void render();

};

}