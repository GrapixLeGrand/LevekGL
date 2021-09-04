#pragma once

#include <string>
#include "../Model.hpp"
#include "../Mesh.hpp"

namespace Levek {
class ModelLoader {
    std::vector<Model*> mModels;
public:
    virtual ~ModelLoader() {
        for (int i = 0; i < mModels.size(); i ++) {
            delete mModels[i];
        }
    };
    virtual Model* loadFromFile(const std::string& path) = 0;
    //virtual Mesh* loadSingleObject(const std::string& path) = 0;
};
}