#pragma once

#include "TextureProperties.hpp"

namespace Levek {

class RenderBuffer {
private:
    unsigned int id;
    int width;
    int height;
    TextureType type;
public:
    RenderBuffer(int width, int height, TextureType type);
    ~RenderBuffer();
    //void attachTexture(const Texture& texture, AttachmentType type);
    void bind() const;
    void unbind() const;

    unsigned int getId() const { return id; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    TextureType getType() const { return type; }

};
};