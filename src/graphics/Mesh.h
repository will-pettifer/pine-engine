//
// Created by will-pettifer on 15/03/2026.
//

#ifndef PINE_ENGINE_MESH_H
#define PINE_ENGINE_MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <memory>
#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  u_int id;
  string path;
};

class Mesh {
public:
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  Texture texture;
  u_int VAO;

  Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Texture texture);

  void Draw(Shader &shader);

private:
  unsigned int VBO, EBO;

  void setupMesh();
};

#endif // PINE_ENGINE_MESH_H
