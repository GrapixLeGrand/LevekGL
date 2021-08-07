#pragma once

#include "MeshLoader.hpp"

namespace Levek {
class AssimpMeshLoader : public MeshLoader {
public:
    AssimpMeshLoader() {};
private:
    virtual Mesh loadFromFile(const std::string& path);
};
}