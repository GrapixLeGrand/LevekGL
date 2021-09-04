#pragma once

#include <unordered_map>
#include <map>
#include <string>

#include "ModelNode.hpp"

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