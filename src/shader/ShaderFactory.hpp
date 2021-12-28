#pragma once

#include "Shader.hpp"

namespace Levek {
class ShaderFactory {
    
public:
    //friend class Shader;
    static Shader makeFromFile(const std::string vertexPath, const std::string fragmentPath);
    static Shader makeFromSource(const std::string vertexSource, const std::string fragmentSource);
    
};
};