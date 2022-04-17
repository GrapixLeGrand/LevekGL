#pragma once

#include "FrameBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

namespace Levek {
class Buffer {
    void bind() const;
    void unbind() const;
    void clear();
};

}