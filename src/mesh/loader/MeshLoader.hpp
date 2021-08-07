#pragma once

#include <string>
#include "../Mesh.hpp"

namespace Levek {
class MeshLoader {
public:
    virtual ~MeshLoader() {};
    virtual Mesh loadFromFile(const std::string& path) = 0;
};
}