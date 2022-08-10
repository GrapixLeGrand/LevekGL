#pragma once

#include "RenderingPass.hpp"
#include "ForwardRenderingState.hpp"
#include <vector>
#include <unordered_map>

namespace Levek {
class ForwardRenderingPass : public RenderingPass {
private:
    std::vector<ForwardRenderingState*> states;
    int nextStateId = 0;
public:

    ForwardRenderingPass(std::vector<ForwardRenderingState>& states);
    ForwardRenderingPass();
    int addState(ForwardRenderingState* state);
    virtual void render();

};
}