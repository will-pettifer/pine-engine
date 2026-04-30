

#ifndef PINE_ENGINE_SHADER_H
#define PINE_ENGINE_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

using namespace std;

class Shader {
public:
  u_int ID;

  void Init(const char *vertexPath, const char *fragmentPath,
            bool tesselation = false);

  void Use() const;

  void setBool(const string &name, bool value) const;

  void setInt(const string &name, int value) const;

  void setFloat(const string &name, float value) const;

  void setVec2(const string &name, const glm::vec2 &value) const;

  void setVec2(const string &name, float x, float y) const;

  void setVec3(const string &name, const glm::vec3 &value) const;

  void setVec3(const string &name, float x, float y, float z) const;

  void setVec4(const string &name, const glm::vec4 &value) const;

  void setVec4(const string &name, float x, float y, float z, float w) const;

  void setMat2(const string &name, const glm::mat2 &mat) const;

  void setMat3(const string &name, const glm::mat3 &mat) const;

  void setMat4(const string &name, const glm::mat4 &mat) const;

private:
  void checkCompileErrors(GLuint shader, string type);
};

#endif // PINE_ENGINE_SHADER_H
