
#include "ShaderManager.hpp"
#include "../OpenGLError.hpp"
#include <GL/glew.h>

namespace Levek {
    std::unordered_map<std::size_t, ShaderMetaData> ShaderManager::shadersMetaData;
    std::unordered_map<unsigned int, std::size_t> ShaderManager::idsToHash;

    unsigned int ShaderManager::compileShader(const std::string& program, unsigned int shaderType, int count, const int* length) {

        unsigned int id = glCreateShader(shaderType);

        const char* p = program.c_str();
        glShaderSource(id, count, &p, length);
        glCompileShader(id);
        int compiled_status = GL_FALSE;
        glGetShaderiv(id, GL_COMPILE_STATUS, &compiled_status);

        std::string shaderTypeStr = shaderType == GL_FRAGMENT_SHADER ? "fragment shader" : "vertex shader";

        if (compiled_status != GL_TRUE) {
            LEVEK_RENDERING_ID_FAIL("failed to compile shader", id);
        }
        else {
            //LEVEK_RENDERING_ID_INFO("shader compilation success (frag/vert)", id);
        }

        return id;
    }

    unsigned int ShaderManager::createShader(const std::string& vertexShader, const std::string& fragmentShader) {

        GL_CHECK(unsigned int program = glCreateProgram());
        GL_CHECK(unsigned int vertexShaderId = compileShader(vertexShader, GL_VERTEX_SHADER, 1, NULL);)
            GL_CHECK(unsigned int fragmentShaderId = compileShader(fragmentShader, GL_FRAGMENT_SHADER, 1, NULL);)
            GL_CHECK(glAttachShader(program, vertexShaderId));
        GL_CHECK(glAttachShader(program, fragmentShaderId));
        GL_CHECK(glLinkProgram(program));

        int isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

        if (!isLinked) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // The program is useless now. So delete it.
            glDeleteProgram(program);
            LEVEK_RENDERING_FAIL(infoLog.data());
        }

        //detaching programs ?
        GL_CHECK(glDetachShader(program, vertexShaderId));
        GL_CHECK(glDetachShader(program, fragmentShaderId));
        GL_CHECK(glDeleteShader(vertexShaderId));
        GL_CHECK(glDeleteShader(fragmentShaderId));

        //LEVEK_RENDERING_ID_INFO("created shader program", program);

        return program;
    }

    int ShaderManager::getUniformLocation(unsigned int id, const std::string& name) {

        //we might want to remove these checks or in realese mod
        if (idsToHash.find(id) == idsToHash.end()) {
            LEVEK_RENDERING_ID_FAIL("Failed to find the id in id to hash table", id);
        }
        std::size_t hash = idsToHash[id];
        if (shadersMetaData.find(hash) == shadersMetaData.end()) {
            LEVEK_RENDERING_ID_FAIL("Failed to find the hash in the hash tabe", id);
        }
        ShaderMetaData& entry = shadersMetaData[hash];

        if (entry.uniformLocationCache.find(name) != entry.uniformLocationCache.end()) {
            return entry.uniformLocationCache[name];
        }

        GL_CHECK(int location = glGetUniformLocation(entry.id, name.c_str()));

        if (location == -1) {
            LEVEK_RENDERING_ID_INFO("uniform not found", entry.id)
                //std::cout << "Warning: uniform " << name << " does not exist" << std::endl;
        }

        entry.uniformLocationCache[name] = location;
        return location;
    }

    unsigned int ShaderManager::requestShader(const std::string& vertexSource, const std::string& fragmentSource) {
        std::string programs = vertexSource + fragmentSource;
        std::size_t hash = std::hash<std::string>{}(programs);

        //shader not found
        if (shadersMetaData.find(hash) == shadersMetaData.end()) {
            //create shader meta data and emplace it
            unsigned int id = createShader(vertexSource, fragmentSource);
            ShaderMetaData data = { id, vertexSource, fragmentSource, 1, {} };
            shadersMetaData[hash] = data;
            idsToHash[id] = hash;
            return id;
        }

        ShaderMetaData& metaData = shadersMetaData[hash];
        metaData.referenceCount += 1;
        return metaData.id;
    }

    void ShaderManager::releaseShader(unsigned int id) {

        if (idsToHash.find(id) == idsToHash.end()) {
            return;
        }
        std::size_t hash = idsToHash[id];
        if (shadersMetaData.find(hash) == shadersMetaData.end()) {
            return;
        }

        ShaderMetaData& entry = shadersMetaData[hash];
        if (entry.referenceCount > 0) {
            entry.referenceCount -= 1;
            if (entry.referenceCount == 0) {
                //LEVEK_RENDERING_ID_INFO("Deleting shader program", entry.id);
                GL_CHECK(glDeleteProgram(entry.id));
                idsToHash.erase(entry.id);
                shadersMetaData.erase(hash);
            }
        }
        else {
            LEVEK_RENDERING_FAIL("bad shader entry in the meta data with reference count 0");
        }

    }

    unsigned int ShaderManager::requestShader(unsigned int id) {

        if (idsToHash.find(id) == idsToHash.end()) {
            LEVEK_RENDERING_ID_FAIL("requested shader not found by id", id);
        }
        std::size_t hash = idsToHash[id];
        if (shadersMetaData.find(hash) == shadersMetaData.end()) {
            LEVEK_RENDERING_ID_FAIL("requested shader not found by hash", id);
        }

        ShaderMetaData& entry = shadersMetaData[hash];
        entry.referenceCount += 1;
        return id;

    }

}