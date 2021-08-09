#pragma once

#include "SceneLoader.hpp"

namespace Levek {
class AssimpSceneLoader : public SceneLoader {
public:
    AssimpSceneLoader() {};
    virtual ~AssimpSceneLoader() {};
private:
    virtual Scene* loadFromFile(const std::string& path);
    virtual Mesh* loadSingleObject(const std::string& path);
};
}