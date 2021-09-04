#pragma once

#include <vector>
#include "../texture/Texture.hpp"

namespace Levek {
    enum TextureType {
        AMBIANT,
        DIFFUSE,
        SPECULAR
    };

class Material {
private:
    std::vector<const Texture*> mTextures;
    std::vector<TextureType> mTexturesTypes;
public:

/**
 * Adds a texture to the material, specifying its type
 * @param
 * @param
 */
void addTexture(const Texture* texture, TextureType type) {
    mTextures.push_back(texture);
    mTexturesTypes.push_back(type);
}

const Texture* getTexture(int index) {
    return mTextures[index];
}

int getTextureType(int index) {
    return mTexturesTypes[index];
}

};
}