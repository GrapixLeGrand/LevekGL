#include "Texture.hpp"
#include "../OpenGLError.hpp"
#include "stb_image.h"
#include <GL/glew.h>

namespace Levek {

Texture::Texture(): PixelBuffer(PixelBufferType::TEXTURE) {
	GL_CHECK(glGenTextures(1, &rendererId));
	this->setId(rendererId);
}

Texture::Texture(const std::string& path)
	: Texture(path, GL_CLAMP_TO_EDGE) {}


void get_stbi_image(const std::string& path, uint8_t** ptr, int& w, int& h, int& bpp) {
	stbi_set_flip_vertically_on_load(1); //flip texture up and down, opengl want the texture to begin on the left bottom corner
	*ptr = stbi_load(path.c_str(), &w, &h, &bpp, 4);
	LEVEK_RENDERING_ASSERT(*ptr, "What?");
}

Texture::Texture(const std::string& path, unsigned int wrapMode)
	: filePath(path), width(0), height(0), bpp(0), rendererId(0), textureType(TextureParameters::RGBA), PixelBuffer(PixelBufferType::TEXTURE) {
	
	//unsigned char* localBuffer = nullptr; //why conserving this ?
	//stbi_set_flip_vertically_on_load(1); //flip texture up and down, opengl want the texture to begin on the left bottom corner
	//localBuffer = stbi_load(path.c_str(), &width, &height, &Bpp, 4); // rgba = 4 channels
	//LEVEK_RENDERING_ASSERT(localBuffer, "local buffer is NULL. Maybe the path to the image is wrong.");
	initFromStbi = true;
	get_stbi_image(path, &data, this->width, this->height, this->bpp);

	GL_CHECK(glGenTextures(1, &rendererId));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, rendererId));
	//maybe google theses terms later
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode));

	//send to opengl
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data)); //0 for no multilevel texture, 0 for border
	GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));

	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
	stbi_set_flip_vertically_on_load(0); //unsetting this for later loads (cube maps need no inversion)
	
}

Texture::Texture(const std::string& path, TextureParameters::TextureWrapMode wrapMode): Texture(path, OPENGL_WRAP_MODES[wrapMode]) {}

Texture::Texture(int width, int height, TextureParameters::TextureType type)
	: Texture(width, height, type, TextureParameters::CLAMP_TO_BORDER, TextureParameters::LINEAR, TextureParameters::LINEAR) {}

Texture::Texture(int width, int height, TextureParameters::TextureType type, TextureParameters::TextureWrapMode wrapMode, 
			TextureParameters::TextureLODFunction minMode, TextureParameters::TextureLODFunction magMode)
		: width(width), height(height), bpp(0), rendererId(0), textureType(type), PixelBuffer(PixelBufferType::TEXTURE) {
	GL_CHECK(glGenTextures(1, &rendererId));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, rendererId));
	
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OPENGL_MIN_MAG_MODES[minMode]));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OPENGL_MIN_MAG_MODES[magMode]));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, OPENGL_WRAP_MODES[wrapMode]));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, OPENGL_WRAP_MODES[wrapMode]));
	
	float whiteBoarder[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GL_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, whiteBoarder));

	const TextureParameters::OpenGLTextureProperties properties = OPENGL_TEXTURES_PROPERTIES[type];

	//send to opengl
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, properties.internalFormat, width, height, 0, properties.format, properties.type, 0)); //0 for no multilevel texture, 0 for border
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}


Texture::~Texture() {
	if (initFromStbi && data != nullptr) {
		stbi_image_free(data);
	}
	GL_CHECK(glDeleteTextures(1, &rendererId))
}

void Texture::activateAndBind(unsigned int slot) const {
	ASSERT(slot >= 0 && slot < 32);
	GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot));
	bind();
}

void Texture::bind() const {
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, rendererId));
}

void Texture::unbind() const {
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::set(TextureParameters::TextureWrapMode wrapMode) {
	bind();
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, OPENGL_WRAP_MODES[wrapMode]));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, OPENGL_WRAP_MODES[wrapMode]));
}

void Texture::set(TextureParameters::TextureLODFunction minMode, TextureParameters::TextureLODFunction magMode) {
	bind();
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OPENGL_MIN_MAG_MODES[minMode]));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OPENGL_MIN_MAG_MODES[magMode]));
	GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
	//GL_CHECK(glGenerateTextureMipmap(rendererId));
}


void Texture::update(const std::string& path) {
	if (initFromStbi && this->data) {
		stbi_image_free(this->data);
	}
	initFromStbi = true;
	get_stbi_image(path, &data, this->width, this->height, this->bpp);

	const TextureParameters::OpenGLTextureProperties properties = OPENGL_TEXTURES_PROPERTIES[TextureParameters::TextureType::RGBA];
	bind();
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, properties.internalFormat, width, height, 0, properties.format, properties.type, data));
}

void Texture::update(uint8_t* data, int w, int h, TextureParameters::TextureType type) {
	if (initFromStbi && this->data) {
		stbi_image_free(this->data);
	}
	initFromStbi = false;
	this->width = w;
	this->height = h;
	const TextureParameters::OpenGLTextureProperties properties = OPENGL_TEXTURES_PROPERTIES[type];
	bind();
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, properties.internalFormat, width, height, 0, properties.format, properties.type, data));
}

const uint8_t* Texture::getData() {
	bind();
	const TextureParameters::OpenGLTextureProperties properties = OPENGL_TEXTURES_PROPERTIES[textureType];
	GL_CHECK(glGetTexImage(GL_TEXTURE_2D, 0, properties.internalFormat, properties.type, this->data));
	return this->data;
}


void Texture::attachToFrameBuffer(FrameBufferProperties::AttachementType type, int index) const {
	int t = OPENGL_ATTACHMENTS[type];
	GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, OPENGL_ATTACHMENTS[type] + index, GL_TEXTURE_2D, rendererId, 0));
}

void Texture::clear(glm::uvec4 color) {
	const TextureParameters::OpenGLTextureProperties properties = OPENGL_TEXTURES_PROPERTIES[textureType];
	//printf("type :%d\n", textureType);
	LEVEK_ASSERT(properties.internalFormat == GL_RGB || properties.internalFormat == GL_RGBA, "The texture must be either RGB or RGBA\n");
	bind();
	GL_CHECK(glClearTexImage(rendererId, 0, properties.format, properties.type, &color[0]));
}

void Texture::clear(glm::vec4 color) {
	const TextureParameters::OpenGLTextureProperties properties = OPENGL_TEXTURES_PROPERTIES[textureType];
	LEVEK_ASSERT(properties.internalFormat == GL_RGBA16F, "The texture must be either RGB or RGBA\n");
	bind();
	GL_CHECK(glClearTexImage(rendererId, 0, properties.format, properties.type, &color[0]));
}


void Texture::clear(float value) {
	const TextureParameters::OpenGLTextureProperties properties = OPENGL_TEXTURES_PROPERTIES[textureType];
	LEVEK_ASSERT(properties.type == GL_FLOAT, "The texture must be of data type float and single component\n");
	bind();
	GL_CHECK(glClearTexImage(rendererId, 0, properties.format, GL_FLOAT, &glm::vec1(value)[0]));
}

void Texture::set(glm::vec4 clampToBorderColor) {
	bind();
	GL_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,  &clampToBorderColor[0]));
}

};