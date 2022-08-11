#pragma once

#include "RenderingPass.hpp"
#include "IForwardRenderingState.hpp"
#include <vector>
#include <unordered_map>

namespace Levek {
class ForwardRenderingPass : public RenderingPass {
private:
    ForwardRenderingPassData data;
    std::vector<IForwardRenderingState*> states;
    int nextStateId = 0;
public:

    ForwardRenderingPass(std::vector<IForwardRenderingState>& states);
    ForwardRenderingPass();
    int addState(IForwardRenderingState* state);
    virtual void render();

};
}