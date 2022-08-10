#pragma once

#include "ForwardRenderingPassData.hpp"

namespace Levek {
class ForwardRenderingState {
public:
    virtual ~ForwardRenderingState() = 0;
    virtual void render(const ForwardRenderingPassData* data) = 0;
};
}