#pragma once

#include <vector>
#include <unordered_map>
#include "../OpenGLError.hpp"

namespace Levek {

template <class T>
class GenericPtrPipelineRegistry {
private:
    std::unordered_map<std::string, int> elems_id_index;
    std::vector<T*> elems;
    T* dummyValue = nullptr;
public:

    GenericPtrPipelineRegistry(T* dummyValueArg): dummyValue(dummyValueArg) {}; 
    void add(T* elem, std::string name) {
        
        LEVEK_ASSERT(elem != nullptr, "element associated to name %s is null\n", name.c_str());
        LEVEK_ASSERT(name.size() > 0, "name cannot have zero length\n");

        if (elems_id_index.find(name) != elems_id_index.end()) {
            LEVEK_WARNING("trying to add an already added element to the registry with name %s, ignoring it\n", name.c_str());
            return;
        }
        elems.push_back(elem);
        elems_id_index[name] = elems.size() - 1;
    }

    T* get(std::string name) {
        LEVEK_ASSERT(name.size() > 0, "name cannot have zero length\n");
        if (elems_id_index.find(name) == elems_id_index.end()) {
            LEVEK_WARNING("failed to find element with name %s in the registry, returning dummy\n", name.c_str());
            return nullptr; //TextureFactory::makePinkRBGA();
        }
        return elems[elems_id_index[name]];
    }

};

template <class T>
class GenericValuePipelineRegistry {
private:
    std::unordered_map<std::string, int> elems_id_index;
    std::vector<T> elems;
    T dummyValue;
public:

    GenericValuePipelineRegistry(T dummyValueArg): dummyValue(dummyValueArg) {};
    void add(T elem, std::string name) {
        
        LEVEK_ASSERT(name.size() > 0, "name cannot have zero length\n");

        if (elems_id_index.find(name) != elems_id_index.end()) {
            LEVEK_WARNING("trying to add an already added element to the registry with name %s, ignoring it\n", name.c_str());
            return;
        }
        elems.push_back(elem);
        elems_id_index[name] = elems.size() - 1;
    }

    T get(std::string name) {
        LEVEK_ASSERT(name.size() > 0, "name cannot have zero length\n");
        if (elems_id_index.find(name) == elems_id_index.end()) {
            LEVEK_WARNING("failed to find element with name %s in the registry, returning dummy\n", name.c_str());
            return dummyValue;
        }
        return elems[elems_id_index[name]];
    }

};

}