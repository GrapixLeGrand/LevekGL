#pragma once

namespace Levek {

class PipelineNode {
    PipelineNode* prev = nullptr;
    PipelineNode* next = nullptr;
public:
    PipelineNode(PipelineNode* argprev, PipelineNode* argnext): prev(argprev), next(argnext) {};

};

}