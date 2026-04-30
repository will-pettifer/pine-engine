//
// Created by will-pettifer on 15/03/2026.
//

#include "Model.h"

#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <fstream>
#include <iostream>
#include <map>

Model::Model(string const &path) { LoadModel(path); }

void Model::Draw(Shader &shader) {
  for (auto &mesh : meshes)
    mesh.Draw(shader);
}

void Model::LoadModel(string const &path) {
  Assimp::Importer importer;
  string fullPath = "assets/models/" + path;
  const aiScene *scene = importer.ReadFile(
      fullPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                    aiProcess_ForceGenNormals | aiProcess_FlipUVs |
                    aiProcess_CalcTangentSpace);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
    return;
  }
  directory = fullPath.substr(0, fullPath.find_last_of('/'));
  ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
  for (u_int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(ProcessMesh(mesh, scene));
  }

  for (u_int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  vector<Vertex> vertices;
  vector<u_int> indices;
  Texture texture;

  for (u_int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex{};
    glm::vec3 vector;

    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;

    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
    }

    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoords = vec;
    } else
      vertex.TexCoords = glm::vec2(0.0f, 0.0f);

    vertices.push_back(vertex);
  }
  for (u_int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (u_int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
  aiString albedoFile;
  if (material->GetTexture(aiTextureType_DIFFUSE, 0, &albedoFile) ==
      AI_SUCCESS) {
    string texPath = albedoFile.C_Str();
    bool skip = false;
    for (auto &loaded : textures_loaded) {
      if (loaded.path == texPath) {
        texture = loaded;
        skip = true;
        break;
      }
    }
    if (!skip) {
      string fullTexPath = directory + "/" + texPath;
      texture.id = TextureFromFile(fullTexPath.c_str());
      texture.path = texPath;
      textures_loaded.push_back(texture);
    }
  }

  return {vertices, indices, texture};
}

u_int Model::TextureFromFile(const char *path) {
  string filename = string(path);

  u_int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  u_char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}