#pragma once

#include "Texture.hpp"
#include <ctype.h>

namespace Levek {
class TextureFactory {

private:
static inline Texture* makeSinglePixel(uint8_t pixel[4]);
public:
static Texture* makePinkRBGA();
static Texture* makeBlackRBGA();
static Texture* makeWhiteRBGA();

};
}