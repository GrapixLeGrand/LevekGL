#pragma once

namespace Levek {

extern const int OPENGL_ATTACHMENTS[3];


class FrameBufferProperties {
public:
    enum AttachementType {
        COLOR,
        DEPTH,
        DEPTH_STENCIL
    };

};

}