
#include "ShaderManager.hpp"

namespace Levek {
    std::unordered_map<std::size_t, ShaderMetaData> ShaderManager::shadersMetaData;
    std::unordered_map<unsigned int, std::size_t> ShaderManager::idsToHash;
}