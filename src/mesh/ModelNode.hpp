#pragma once

#include <vector>
#include <string>

#include "Mesh.hpp"
#include "Material.hpp"
#include "Transform.hpp"

namespace Levek {
class ModelNode {
private:

    std::string mName;

    ModelNode* mParent = nullptr;
    std::vector<ModelNode*> mChildren;

    std::vector<int> mMeshes;

    Transform mTransform;

    Model* mScene = nullptr;

public:

    ModelNode(Model* scene, const std::string& name, ModelNode* parent):
        mName(name), mParent(parent), mScene(scene) {}

    /*
    void addMesh(Mesh* mesh, Material* material, Transform* transform) {
        //mMeshes.push_back(mesh);
        //mMaterials.push_back(material);
        //mTransforms.push_back(transform);
    }*/

    const Transform& getTransform() {
        return mTransform;
    }

    //getters
    const std::vector<int>& getMeshes() {
        return mMeshes;
    }

    /*
    const std::vector<int>& getMaterials() {
        return mMaterials;
    }*/

    bool hasChildren() {
        return mChildren.size() != 0;
    }

    bool isRoot() {
        return mParent == nullptr;
    }

};
}