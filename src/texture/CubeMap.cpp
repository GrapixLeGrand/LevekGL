#include "CubeMap.hpp"

#include <GL/glew.h>
#include "../OpenGLError.hpp"

namespace Levek {
    CubeMap::CubeMap(int width, int height, TextureParameters::TextureType type) {

    }

    CubeMap::CubeMap(const std::vector<std::string>& texturesPaths, size_t width, size_t heigth) :
        mTexturesPaths(texturesPaths), mWidth(width), mHeight(heigth) {

        LEVEK_RENDERING_ASSERT(texturesPaths.size() == 6, "must have 6 images of same size to proceed");
        GL_CHECK(glGenTextures(1, &mId));
        GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, mId));

        unsigned char* data = nullptr;
        int w, h, c;
        for (size_t i = 0; i < texturesPaths.size(); i++) {

            data = stbi_load(texturesPaths[i].c_str(), &w, &h, &c, 0);
            LEVEK_RENDERING_ASSERT(w == (int)mWidth && h == (int)mHeight, 
            "cubemap width or height not same as initialized, or the path to the image is wrong...");
            GL_CHECK(glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + (unsigned int)i,
                0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            ));

            if (data != nullptr) {
                stbi_image_free(data);
            }

        }

        GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

    }

    CubeMap::~CubeMap() {
        GL_CHECK(glDeleteTextures(1, &mId));
    }

    void CubeMap::bind() const {
        GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, mId));
    }

    void CubeMap::unbind() const {
        GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
    }

    unsigned int CubeMap::getId() const {
        return mId;
    }
};