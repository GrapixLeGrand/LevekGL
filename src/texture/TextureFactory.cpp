#include "TextureFactory.hpp"

namespace Levek {

inline Texture* TextureFactory::makeSinglePixel(uint8_t pixel[4]) {
    Texture* tex = new Texture();
    tex->update(pixel, 1, 1, Levek::TextureParameters::TextureType::RGBA);
    tex->set(Levek::TextureParameters::TextureWrapMode::REPEAT);
    return tex;
}

Texture* TextureFactory::makePinkRBGA() {
    uint8_t pixel[4] = {255, 51, 204, 255};
    return makeSinglePixel(pixel);
}

Texture* TextureFactory::makeBlackRBGA() {
    uint8_t pixel[4] = {0, 0, 0, 255};
    return makeSinglePixel(pixel);
}

Texture* TextureFactory::makeWhiteRBGA() {
    uint8_t pixel[4] = {255, 255, 255, 255};
    return makeSinglePixel(pixel);
}

}