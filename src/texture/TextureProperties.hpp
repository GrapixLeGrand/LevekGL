#pragma once


//#include "../renderer/Renderer.h"

namespace Levek {

namespace TextureParameters {

enum TextureType {
	RGB,
	RGBA,				//32 bits each 8 bits channels
	DEPTH,			//24 bits single channel
	DEPTH_STENCIL, 	//24 bits for the depth and 8 bits for stencil (TODO)
	RGBA_FLOAT,
	R_FLOAT
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
	int internalFormat; //component wise bit use (I think)
	int format; //component R G B A
	int type; //type of each component: byte, float etc..
};

};

#define OPENGL_TEXTURES_PROPERTIES_N 6
#define OPENGL_WRAP_MODES_N 4
#define OPENGL_MIN_MAG_MODES_N 2

extern const TextureParameters::OpenGLTextureProperties OPENGL_TEXTURES_PROPERTIES[OPENGL_TEXTURES_PROPERTIES_N];
extern const int OPENGL_WRAP_MODES[OPENGL_WRAP_MODES_N];
extern const int OPENGL_MIN_MAG_MODES[OPENGL_MIN_MAG_MODES_N];

};