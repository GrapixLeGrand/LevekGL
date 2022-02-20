#pragma once

#include <string>
#include <GL/glew.h>
//#include "../renderer/Renderer.h"
#include "TextureProperties.hpp"

namespace Levek {

class Texture
{
private:
	unsigned int rendererId;
	std::string filePath;
	unsigned char* localBuffer; //why conserving this ?
	int width, height, Bpp;
	TextureType textureType;
public:
	Texture(const std::string& path);
	Texture(const std::string& path, unsigned int wrapMode);
	Texture(const std::string& path, TextureWrapMode wrapMode);
	Texture(int width, int height, TextureType type, TextureWrapMode wrapMode, 
		TextureLODFunction minMode, TextureLODFunction magMode);
	Texture(int width, int height, TextureType type);
	~Texture();

	void activateAndBind(unsigned int slot = 0) const; //various slots because you want to bind multiple textures at the same time
	void bind() const;
	void unbind() const;

	inline int getWidth()  const { return width; }
	inline int getHeight() const { return height; }
	
	unsigned int getId() const { return rendererId; }
	TextureType getType() const { return textureType; }
};
};