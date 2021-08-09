#pragma once

#include <string>
#include "../Scene.hpp"
#include "../Mesh.hpp"

namespace Levek {
class SceneLoader {
public:
    virtual ~SceneLoader() {};
    virtual Scene* loadFromFile(const std::string& path) = 0;
    virtual Mesh* loadSingleObject(const std::string& path) = 0;
};
}