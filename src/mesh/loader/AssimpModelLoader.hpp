#pragma once

#include "ModelLoader.hpp"

namespace Levek {
class AssimpModelLoader : public ModelLoader {
public:
    AssimpModelLoader() {};
    virtual ~AssimpModelLoader() {};
private:
    virtual Model* loadFromFile(const std::string& path);
};
}