#pragma once

#include <vector>
#include "../buffer/FrameBuffer.hpp"
#include "../texture/PixelBuffer.hpp"

namespace Levek {

class IPipelineStageOutDescriptor {
public:

    FrameBuffer* fbOut;
    std::vector<std::pair<PixelBufferType, int>> colorsAttachmentsOut;
    std::pair<PixelBufferType, int> depthTextureAttachmentOut = std::make_pair(PixelBufferType::TEXTURE, -1);
    std::pair<PixelBufferType, int> depthStencilAttachmentOut = std::make_pair(PixelBufferType::TEXTURE, -1);

    virtual ~IPipelineStageOutDescriptor() = 0;

    
};
}