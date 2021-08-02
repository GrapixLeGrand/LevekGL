#include "Texture.hpp"
#include "../OpenGLError.hpp"
#include "stb_image.h"

namespace Levek {

Texture::Texture(const std::string& path)
	: Texture(path, GL_CLAMP_TO_EDGE) {}

Texture::Texture(const std::string& path, unsigned int wrapMode)
	: filePath(path), localBuffer(nullptr), width(0), height(0), Bpp(0), rendererId(0), textureType(RGBA_8) {
	stbi_set_flip_vertically_on_load(1); //flip texture up and down, opengl want the texture to begin on the left bottom corner
	localBuffer = stbi_load(path.c_str(), &width, &height, &Bpp, 4); // rgba = 4 channels
	GL_CHECK(glGenTextures(1, &rendererId));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, rendererId));
	//maybe google theses terms later
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode));

	//send to opengl
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer)); //0 for no multilevel texture, 0 for border
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}
	else {
		ASSERT(false);
	}
}

Texture::Texture(int width, int height, TextureType type)
	: Texture(width, height, type, CLAMP_TO_BORDER, LINEAR, LINEAR) {}

Texture::Texture(int width, int height, TextureType type, TextureWrapMode wrapMode, 
			TextureLODFunction minMode, TextureLODFunction magMode)
		: width(width), height(height), Bpp(0), localBuffer(nullptr), rendererId(0), textureType(type) {
	GL_CHECK(glGenTextures(1, &rendererId));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, rendererId));
	
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OPENGL_MIN_MAG_MODES[minMode]));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OPENGL_MIN_MAG_MODES[magMode]));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, OPENGL_WRAP_MODES[wrapMode]));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, OPENGL_WRAP_MODES[wrapMode]));
	
	float whiteBoarder[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GL_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, whiteBoarder));

	const OpenGLTextureProperties properties = OPENGL_TEXTURES_PROPERTIES[type];

	//send to opengl
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, properties.internalFormat, width, height, 0, properties.format, properties.type, 0)); //0 for no multilevel texture, 0 for border
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}


Texture::~Texture() {
	GL_CHECK(glDeleteTextures(1, &rendererId))
}

void Texture::activateAndBind(unsigned int slot) const {
	ASSERT(slot >= 0 && slot < 32);
	GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot))
	bind();
}

void Texture::bind() const {
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, rendererId));
}

void Texture::unbind() const {
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

};