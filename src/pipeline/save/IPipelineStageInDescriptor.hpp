#pragma once

#include <vector>
#include "../buffer/FrameBuffer.hpp"
#include "../texture/PixelBuffer.hpp"

namespace Levek {

class IPipelineStageInDescriptor {
private:
    FrameBuffer* in;
    std::vector<int> textures;
public:
    virtual ~IPipelineStageInDescriptor() = 0;
    IPipelineStageInDescriptor();

};
}