#pragma once

#include "ModelLoader.hpp"
#include <unordered_map>

namespace Levek {

struct ModelPaylaod {
    std::string path;
    std::string name;
    Model* model;
};

class AssimpModelLoader : public ModelLoader {
    std::unordered_map<Model*, ModelPaylaod> mModelsTable;
public:
    AssimpModelLoader() {};
    virtual ~AssimpModelLoader() {
        for (auto& it: mModelsTable) {
            delete it.second.model;
        }
    };
private:
    virtual Model* loadFromFile(const std::string& path);
};
}