#pragma once

#include <vector>
#include <unordered_map>
#include "../texture/Texture.hpp"
#include "../texture/RenderBuffer.hpp"
#include "../OpenGLError.hpp"
#include "../texture/TextureFactory.hpp"
#include "GenericPipelineRegistry.hpp"
#include "../scene/CameraBase.hpp"

namespace Levek {
class PipelineRegistry {
public:
    GenericValuePipelineRegistry<glm::mat4> matrices4 = GenericValuePipelineRegistry<glm::mat4>(glm::mat4(1.0));
    GenericPtrPipelineRegistry<Texture> textures = GenericPtrPipelineRegistry<Texture>(TextureFactory::makePinkRBGA());
    //GenericPtrPipelineRegistry<CameraBase> cameras;
};
}