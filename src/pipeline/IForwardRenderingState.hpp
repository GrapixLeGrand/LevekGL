#pragma once

#include "ForwardRenderingPassData.hpp"

namespace Levek {
class IForwardRenderingState {
public:
    virtual ~IForwardRenderingState() = 0;
    virtual void render(const ForwardRenderingPassData* data) = 0;
};
}