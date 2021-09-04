
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "AssimpModelLoader.hpp"

namespace Levek {
    
    inline glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from)
    {
        glm::mat4 to;

        to[0][0] = (float)from.a1; to[0][1] = (float)from.b1;  to[0][2] = (float)from.c1; to[0][3] = (float)from.d1;
        to[1][0] = (float)from.a2; to[1][1] = (float)from.b2;  to[1][2] = (float)from.c2; to[1][3] = (float)from.d2;
        to[2][0] = (float)from.a3; to[2][1] = (float)from.b3;  to[2][2] = (float)from.c3; to[2][3] = (float)from.d3;
        to[3][0] = (float)from.a4; to[3][1] = (float)from.b4;  to[3][2] = (float)from.c4; to[3][3] = (float)from.d4;

        return to;
    }

Model* AssimpModelLoader::loadFromFile(const std::string& path) {

    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
        LEVEK_RENDERING_FAIL(import.GetErrorString()); 
    }

    Model* model = new Model(path); //WARNING: Need to store its reference

    size_t meshNumber = scene->mRootNode->mNumChildren; //for now we only take the direct children
    //std::vector<SceneData> result;
        for (size_t i = 0; i < meshNumber; i++) {
            aiNode* node = scene->mRootNode->mChildren[i];

            if (node->mNumMeshes) {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];

                if (!mesh->HasFaces() || !mesh->HasNormals() || !mesh->HasPositions() || !mesh->HasTextureCoords(0)) {
                    LEVEK_ILLEGAL_STATE("the mesh must have faces, normals, positions and uv");    
                }

                std::shared_ptr<SurfaceMesh> surfaceMesh = ProcessMesh(mesh);
                PhysicalState physicalState = GetMeshPhysicalState(scene, mesh);
                glm::mat4 meshModelMatrix = aiMatrix4x4ToGlm(node->mTransformation);
            
                glm::vec3 scale;
                glm::quat rotation;
                glm::vec3 translation;
                glm::vec3 skew;
                glm::vec4 perspective;
                glm::decompose(meshModelMatrix, scale, rotation, translation, skew,perspective);
                rotation=glm::conjugate(rotation);
                glm::vec3 rotationXYZ(glm::eulerAngles(rotation));
                result.push_back({*surfaceMesh.get(), Transform(translation, rotation, scale), physicalState});
            }
        }

    return model;
}

//bellow is to be trashed after
    std::shared_ptr<SurfaceMesh> ProcessMesh(aiMesh* mesh) {

        if (!mesh->HasFaces() || !mesh->HasNormals() || !mesh->HasPositions() || !mesh->HasTextureCoords(0)) {
            LEVEK_ILLEGAL_STATE("the mesh must have faces, normals, positions and uv");    
        }

        size_t verticesNumber = mesh->mNumVertices;
        size_t indicesNumber = mesh->mNumFaces * 3;
        std::vector<Vertex> vertexBuffer;
        vertexBuffer.reserve(verticesNumber);

        std::vector<unsigned int> indexBuffer;
        indexBuffer.reserve(indicesNumber);

        for (size_t i = 0; i < mesh->mNumVertices; i ++) {

            Vertex vertex;
            //get the position
            aiVector3D* position = &mesh->mVertices[i];
            vertex.position = glm::vec3(position->x, position->y, position->z);
            //mVertices.push_back({position->x, position->y, position->z});
            
            //get the normal
            aiVector3D* normal = &mesh->mNormals[i];
            vertex.normal = glm::vec3(normal->x, normal->y, normal->z);
            //mNormals.push_back({normal->x, normal->y, normal->z});

            if(mesh->mTextureCoords[0]) {
                //get the texture coords if present
                aiVector3D* tex = &mesh->mTextureCoords[0][i];
                vertex.textureCoord = glm::vec2(tex->x, tex->y);
                //mTextureCoords.push_back({tex->x, tex->y});
            } else {
                vertex.textureCoord = glm::vec2(0.0);
                //mTextureCoords.push_back({0, 0});
            }
            vertexBuffer.push_back(vertex);
        }

        for (size_t i = 0; i < mesh->mNumFaces; i++) {
            aiFace* face = &mesh->mFaces[i];
            if (face->mNumIndices != 3) {
                LEVEK_ILLEGAL_STATE("Surface Mesh model must have triangle faces with 3 indices");
            }
            indexBuffer.push_back(face->mIndices[0]);
            indexBuffer.push_back(face->mIndices[1]);
            indexBuffer.push_back(face->mIndices[2]);    
        }
        return std::make_shared<SurfaceMesh>(vertexBuffer, indexBuffer);
    }

    PhysicalState GetMeshPhysicalState(const aiScene* scene, const aiMesh* mesh) {
        if(mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiString name = material->GetName();
            if (!strncmp(name.C_Str(), "dynamic", 20)) {
                return DYNAMIC;
            } else if (!strncmp(name.C_Str(), "static", 20)) {
                return STATIC;
            } else {
                return NONE;
            }
        } else {
            return NONE;
        }
    }

    //modified from https://stackoverflow.com/questions/29184311/how-to-rotate-a-skinned-models-bones-in-c-using-assimp
    inline glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from)
    {
        glm::mat4 to;


        to[0][0] = (float)from.a1; to[0][1] = (float)from.b1;  to[0][2] = (float)from.c1; to[0][3] = (float)from.d1;
        to[1][0] = (float)from.a2; to[1][1] = (float)from.b2;  to[1][2] = (float)from.c2; to[1][3] = (float)from.d2;
        to[2][0] = (float)from.a3; to[2][1] = (float)from.b3;  to[2][2] = (float)from.c3; to[2][3] = (float)from.d3;
        to[3][0] = (float)from.a4; to[3][1] = (float)from.b4;  to[3][2] = (float)from.c4; to[3][3] = (float)from.d4;

        return to;
    }

public:
    std::vector<SceneData> Load(const std::string& filePath) {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
            LEVEK_ILLEGAL_STATE(import.GetErrorString());
        }

        size_t meshNumber = scene->mRootNode->mNumChildren; //for now we only take the direct children
        std::vector<SceneData> result;
        for (size_t i = 0; i < meshNumber; i++) {
            aiNode* node = scene->mRootNode->mChildren[i];

            if (node->mNumMeshes) {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];

                if (!mesh->HasFaces() || !mesh->HasNormals() || !mesh->HasPositions() || !mesh->HasTextureCoords(0)) {
                    LEVEK_ILLEGAL_STATE("the mesh must have faces, normals, positions and uv");    
                }

                std::shared_ptr<SurfaceMesh> surfaceMesh = ProcessMesh(mesh);
                PhysicalState physicalState = GetMeshPhysicalState(scene, mesh);
                glm::mat4 meshModelMatrix = aiMatrix4x4ToGlm(node->mTransformation);
            
                glm::vec3 scale;
                glm::quat rotation;
                glm::vec3 translation;
                glm::vec3 skew;
                glm::vec4 perspective;
                glm::decompose(meshModelMatrix, scale, rotation, translation, skew,perspective);
                rotation=glm::conjugate(rotation);
                glm::vec3 rotationXYZ(glm::eulerAngles(rotation));
                result.push_back({*surfaceMesh.get(), Transform(translation, rotation, scale), physicalState});
            }
        }

        return result;
    }



}