#pragma once

#include <vector>
#include <string>

#include "Mesh.hpp"

namespace Levek {
class Model {

private:
    const std::string mPath;
    std::vector<Mesh*> mMeshes;
public:
    Model(const std::string& path): mPath(path) {
        //here use ModelLoader
    }

};
}