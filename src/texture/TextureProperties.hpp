#pragma once

#include <GL/glew.h>
//#include "../renderer/Renderer.h"

namespace Levek {

enum TextureType {
	RGB_8,
	RGBA_8,				//32 bits each 8 bits channels
	DEPTH_24,			//24 bits single channel
	DEPTH_24_STENCIL_8 	//24 bits for the depth and 8 bits for stencil (TODO)
};

enum TextureWrapMode {
	CLAMP_TO_EDGE,
	CLAMP_TO_BORDER,
	MIRRORED_REPEAT,
	REPEAT,
};

enum TextureLODFunction {
	LINEAR,
	NEAREST
};

struct OpenGLTextureProperties {
	int internalFormat;
	int format;
	int type;
};

#define OPENGL_TEXTURES_PROPERTIES_N 4
#define OPENGL_WRAP_MODES_N 4
#define OPENGL_MIN_MAG_MODES_N 2

extern const OpenGLTextureProperties OPENGL_TEXTURES_PROPERTIES[OPENGL_TEXTURES_PROPERTIES_N];
extern const int OPENGL_WRAP_MODES[OPENGL_WRAP_MODES_N];
extern const int OPENGL_MIN_MAG_MODES[OPENGL_MIN_MAG_MODES_N];

};