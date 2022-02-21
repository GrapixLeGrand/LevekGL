
#include "TextureProperties.hpp"

namespace Levek {
//this table hold properties about Textures of opengl
const TextureParameters::OpenGLTextureProperties OPENGL_TEXTURES_PROPERTIES[OPENGL_TEXTURES_PROPERTIES_N] = {
	{ GL_RGB, GL_RGB, GL_UNSIGNED_BYTE }, //simple RGB channels
	{ GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE }, //RGBA channels, each channel is 8 bits
	{ GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT }, //single depth channel 24 bits
	{ GL_DEPTH24_STENCIL8, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT_24_8 } //single depth channel 24 bits and 8 bits stencil
};

const int OPENGL_WRAP_MODES[OPENGL_WRAP_MODES_N] = {
	GL_CLAMP_TO_EDGE,
	GL_CLAMP_TO_BORDER,
	GL_MIRRORED_REPEAT,
	GL_REPEAT
};

const int OPENGL_MIN_MAG_MODES[OPENGL_MIN_MAG_MODES_N] = {
	GL_LINEAR,
	GL_NEAREST
};
};