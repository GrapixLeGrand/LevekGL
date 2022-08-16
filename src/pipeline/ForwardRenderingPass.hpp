#pragma once

#include "RenderingPass.hpp"
#include "IForwardRenderingState.hpp"
#include <vector>
#include <unordered_map>

#include "PipelineRegistry.hpp"

namespace Levek {
class ForwardRenderingPass : public RenderingPass {
private:
    ForwardRenderingPassData data;
    std::vector<IForwardRenderingState*> states;
public:
    //ForwardRenderingPass(std::vector<IForwardRenderingState>& states);
    ForwardRenderingPass(PipelineRegistry* registry); //: RenderingPass(registry) {};
    int addState(IForwardRenderingState* state);
    virtual void render();

};
}