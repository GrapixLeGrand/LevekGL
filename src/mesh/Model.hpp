#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Transform.hpp"

#include "Mesh.hpp"

namespace Levek {
class Model {

private:
    const std::string mPath;
    std::vector<Mesh*> mMeshes;
    std::vector<Transform*> mTransforms;
public:
    //should be only instanciated by the loader I think
    Model(const std::string& path): mPath(path) {
        //here use ModelLoade 
        std::cout << "I do nothing for now" << std::endl;
    }

    void addMesh(Mesh* mesh, Transform* transform) {
        mMeshes.push_back(mesh);
        mTransforms.push_back(transform);
    }

    const Mesh* getMesh(std::size_t i) {
        return mMeshes[i];
    }

    const Transform* getTransform(std::size_t i) {
        return mTransforms[i];
    }

    size_t getNumMeshes() const {
        return mMeshes.size();
    }

    /* too prematured
    std::pair<const Mesh*, const Transform*> operator[](size_t i) {
        return std::make_pair(mMeshes[i], mTransforms[i]);
    }*/

};
}