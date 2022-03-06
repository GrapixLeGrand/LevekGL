#pragma once


#include <string>
#include <unordered_map>
#include "Shader.hpp"

namespace Levek {

struct ShaderMetaData {
    unsigned int id;
    std::string vertexSource;
    std::string fragmentSource;
    int referenceCount;
    std::unordered_map<std::string, int> uniformLocationCache;
};

class ShaderManager {
private:
    ShaderManager() {}
    friend class Shader;
    static std::unordered_map<std::size_t, ShaderMetaData> shadersMetaData;
    static std::unordered_map<unsigned int, std::size_t> idsToHash;
    static unsigned int compileShader(const std::string& program, unsigned int shaderType, int count, const int* length);
    static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

/**
 * 
 */
    static int getUniformLocation(unsigned int id, const std::string& name);

protected:

    static unsigned int requestShader(const std::string& vertexSource, const std::string& fragmentSource);

    static void releaseShader(unsigned int id);

    static unsigned int requestShader(unsigned int id);


};
}
