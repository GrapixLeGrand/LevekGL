
#include "ShaderFactory.hpp"

namespace Levek
{
    Shader* ShaderFactory::makeFromFile(const std::string vertexPath, const std::string fragmentPath) {
        Shader* shader = new Shader();
        shader->inizializeFromFile(vertexPath, fragmentPath);
        return shader;
    }

    Shader* ShaderFactory::makeFromSource(const std::string vertexSource, const std::string fragmentSource) {
        Shader* shader = new Shader();
        shader->inizializeFromSource(vertexSource, fragmentSource);
        return shader;
    }

}

