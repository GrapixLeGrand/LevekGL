#include <vector>
#include <string>

#include "stb_image.h"
#include "TextureProperties.hpp"

namespace Levek {

class CubeMap {

private:

    std::vector<std::string> mTexturesPaths;
    unsigned int mId = 0;
    size_t mWidth = 0;
    size_t mHeight = 0;

public:
    
    CubeMap(int width, int height, TextureParameters::TextureType type);
    CubeMap(const std::vector<std::string>& texturesPaths, size_t width, size_t heigth);
    ~CubeMap();
    void bind() const;
    void unbind() const;
    unsigned int getId() const;

};
}