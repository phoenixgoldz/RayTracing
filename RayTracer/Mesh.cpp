#include "Mesh.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

bool Mesh::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    // check cast ray with mesh triangles 
    for (size_t i = 0; i < m_objects.size(); ++i)
    {
        if (m_objects[i]->Hit(ray, minDistance, maxDistance, raycastHit))
        {
            return true;
        }
    }

    return false;
}

bool Mesh::Load(const std::string& filename, const glm::vec3& translate, const glm::vec3& rotation, const glm::vec3& scale)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Could not load assimp file " << filename << " error string: " << importer.GetErrorString();
        return false;
    }

    // create transform matrix
    glm::mat4 mt = glm::translate(translate);
    glm::mat4 mr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
    glm::mat4 ms = glm::scale(scale);

    glm::mat4 mx = mt * mr * ms;

    // process the nodes starting at the root
    ProcessNode(scene->mRootNode, scene, mx);

    return true;
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& transform)
{
    // process the current node meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene, transform);
    }
    // process the current node children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, transform);
    }
}

void Mesh::ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform)
{
    // get mesh index vertices
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        // get mesh face, face holds three indices (triangle) into the positions of the mesh
        aiFace face = mesh->mFaces[i];
        if (face.mNumIndices == 3)
        {
            // Add a triangle to the mesh for each face
            m_objects.push_back(std::make_unique<Triangle>(
                glm::vec3(transform * glm::vec4{ mesh->mVertices[face.mIndices[0]].x, mesh->mVertices[face.mIndices[0]].y, mesh->mVertices[face.mIndices[0]].z, 1 }),
                glm::vec3(transform * glm::vec4{ mesh->mVertices[face.mIndices[1]].x, mesh->mVertices[face.mIndices[1]].y, mesh->mVertices[face.mIndices[1]].z, 1 }),
                glm::vec3(transform * glm::vec4{ mesh->mVertices[face.mIndices[2]].x, mesh->mVertices[face.mIndices[2]].y, mesh->mVertices[face.mIndices[2]].z, 1 }),
                m_material));
        }
    }
}
