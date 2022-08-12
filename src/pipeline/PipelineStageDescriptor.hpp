#pragma once

#include "IPipelineStageInDescriptor.hpp"
#include "IPipelineStageOutDescriptor.hpp"

namespace Levek {
class PipelineStageDescriptor {
private:
public:
    PipelineStageDescriptor(IPipelineStageOutDescriptor* from, IPipelineStageInDescriptor* to) {

    }
};
}
/**


PipelineDescriptorOut(
    depthPass,
    { "depthAttachment", 0}
).to(

)

/////////////////////////////////////////

passes = [depth, forward, deffered];
passesInDescriptors = [ (depth, InDesc), (forward, InDesc), (deffered, InDesc)];
passesInDescriptors = [ (depth, InDesc), (forward, InDesc), (deffered, InDesc)];



/////////////////////////////////////////

PipelineStageDescriptorOut(
    depthPass,
    texturesOut : { ("depthAttachment", 0) },
    PipelineDescriptorIn(
        forwardPass,
        texturesIn : { ("DepthTex", 0) },
        PipelineStageDescriptorOut(
            forwardPass,
            texturesOut : { ("colorAttachment" : 0), ("depthStencil", 1) },
            PipelineStageInDescriptor(
                deferredPass,
                textures : { { "otherColor" : 0}, {"otherDepthStencil" : 1} }
            )
        )
    )
)

PipelineDescriptorIn(
    ForwardPass,
    PipelineStageDescriptorOut(
        depthPass
    ),
    {
        ("depthAttachment", 0)
    },
    {
        ("depthTex", 0)
    }
)


PipelineStageDescriptor(
    depthPass, 
    ForwardPass,

)



 * 
 */