//
// Created by will-pettifer on 15/03/2026.
//

#ifndef PINE_ENGINE_MODEL_H
#define PINE_ENGINE_MODEL_H

#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Mesh.h"
#include "Shader.h"

#include <memory>
#include <string>
#include <vector>
using namespace std;

class Model {
public:
  vector<Texture> textures_loaded;
  vector<Mesh> meshes;
  string directory;

  explicit Model(string const &path = "cube/cube.obj");

  void Draw(Shader &shader);

private:
  void LoadModel(string const &path);

  void ProcessNode(aiNode *node, const aiScene *scene);

  Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

  u_int TextureFromFile(const char *path);
};

#endif // PINE_ENGINE_MODEL_H
