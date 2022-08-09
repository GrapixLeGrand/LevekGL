#pragma once

#include "TextureProperties.hpp"

namespace Levek {

class RenderBuffer {
private:
    unsigned int id;
    int width = 0;
    int height = 0;
    TextureParameters::TextureType type;
public:
    RenderBuffer();
    RenderBuffer(int width, int height, TextureParameters::TextureType type);
    ~RenderBuffer();
    //void attachTexture(const Texture& texture, AttachmentType type);
    void bind() const;
    void unbind() const;

    /**
     * @brief update the dimension and the type of the object (NOT SURE IF CALLING MULTIPLE TIMES IS AN ISSUE)
     * 
     * @param w 
     * @param h 
     * @param type 
     */
    void update(int w, int h, TextureParameters::TextureType type);

    unsigned int getId() const { return id; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    TextureParameters::TextureType getType() const { return type; }

};
};