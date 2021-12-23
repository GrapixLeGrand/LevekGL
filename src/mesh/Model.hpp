#pragma once

#include <vector>
#include <string>

#include "Transform.hpp"

#include "Mesh.hpp"

namespace Levek {
class Model {

private:
    const std::string mPath;
    std::vector<Mesh*> mMeshes;
    std::vector<Transform> mTransform;
public:
    //should be only instanciated by the loader I think
    Model(const std::string& path): mPath(path) {
        //here use ModelLoader
    }

    void addMesh(Mesh* mesh, Transform transform) {
        mMeshes.push_back(mesh);
        mTransform.push_back(transform);
    }

};
}