#include "ForwardRenderingPass.hpp"

namespace Levek {
    ForwardRenderingPass::ForwardRenderingPass(PipelineRegistry* registry): RenderingPass(registry) {};
    
    int ForwardRenderingPass::addState(IForwardRenderingState* state) {
        return 1;
    }

    void ForwardRenderingPass::render() {

    } 
}