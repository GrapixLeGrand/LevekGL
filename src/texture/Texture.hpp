#pragma once

#include <string>
//#include "../renderer/Renderer.h"
#include "TextureProperties.hpp"
#include "PixelBuffer.hpp"

namespace Levek {


/**
 * @brief Texture wrapper class.
 * 
 */
class Texture : public PixelBuffer
{
private:
	unsigned int rendererId;
	std::string filePath;
	int width = 0, height = 0, bpp = 0;
	TextureParameters::TextureType textureType;
	uint8_t* data = nullptr;
	bool initFromStbi = false;
public:

	Texture();

	/**
	 * @brief Construct a new Texture object of type RGBA
	 * The dimensions are determined by the image at path
	 * @param path 
	 */
	Texture(const std::string& path);

	/**
	 * @brief Construct a new Texture object of type RGBA
	 * The dimensions are determined by the image at path
	 * @param path 
	 * @
	 */
	Texture(const std::string& path, unsigned int wrapMode);
	Texture(const std::string& path, TextureParameters::TextureWrapMode wrapMode);
	Texture(int width, int height, TextureParameters::TextureType type, TextureParameters::TextureWrapMode wrapMode, 
		TextureParameters::TextureLODFunction minMode, TextureParameters::TextureLODFunction magMode);
	Texture(int width, int height, TextureParameters::TextureType type);
	~Texture();

	void update(const std::string& filename);
	void update(uint8_t* data, int w, int h, TextureParameters::TextureType type);
	//void update(uint8_t* data, int w, int h, TextureParameters::TextureType type);

	void activateAndBind(unsigned int slot = 0) const; //various slots because you want to bind multiple textures at the same time
	virtual void bind() const;
	virtual void unbind() const;

	void set(TextureParameters::TextureWrapMode wrapMode);
	void set(TextureParameters::TextureLODFunction minMode, TextureParameters::TextureLODFunction magMode);

	inline int getWidth()  const { return width; }
	inline int getHeight() const { return height; }
	const uint8_t* getData();

	unsigned int getId() const { return rendererId; }
	TextureParameters::TextureType getType() const { return textureType; }
	
	virtual void attachToFrameBuffer(FrameBufferProperties::AttachementType type, int index = 0) const;
};
};