#include "FrameBufferProperties.hpp"
#include <GL/glew.h>
namespace Levek {
    
    const int OPENGL_ATTACHMENTS[3] = {
        GL_COLOR_ATTACHMENT0,
        GL_DEPTH_ATTACHMENT,
        GL_DEPTH_STENCIL_ATTACHMENT
    };

}