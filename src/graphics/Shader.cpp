//
// Created by will-pettifer on 15/03/2026.
//

#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Shader::Init(const char *vertexPath, const char *fragmentPath,
                  bool tesselation) {
  string tcsPath = "assets/shaders/tcs.glsl";
  string tesPath = "assets/shaders/tes.glsl";
  string vertexCode;
  string fragmentCode;
  string tcsCode;
  string tesCode;
  ifstream vShaderFile;
  ifstream fShaderFile;
  ifstream tcsShaderFile;
  ifstream tesShaderFile;

  vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
  fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
  tcsShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
  tesShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    if (tesselation) {
      tcsShaderFile.open(tcsPath);
      tesShaderFile.open(tesPath);
      stringstream tcsShaderStream, tesShaderStream;
      tcsShaderStream << tcsShaderFile.rdbuf();
      tesShaderStream << tesShaderFile.rdbuf();
      tcsShaderFile.close();
      tesShaderFile.close();
      tcsCode = tcsShaderStream.str();
      tesCode = tesShaderStream.str();
    }
  } catch (ifstream::failure &e) {
    cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << endl;
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  u_int vertex, fragment;

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");

  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);

  u_int tcs = 0, tes = 0;
  if (tesselation) {
    const char *tcsShaderCode = tcsCode.c_str();
    const char *tesShaderCode = tesCode.c_str();

    tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tcs, 1, &tcsShaderCode, NULL);
    glCompileShader(tcs);
    checkCompileErrors(tcs, "TESS_CONTROL");

    tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tes, 1, &tesShaderCode, NULL);
    glCompileShader(tes);
    checkCompileErrors(tes, "TESS_EVALUATION");

    glAttachShader(ID, tcs);
    glAttachShader(ID, tes);
  }

  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  if (tcs)
    glDeleteShader(tcs);
  if (tes)
    glDeleteShader(tes);
}

void Shader::Use() const { glUseProgram(ID); }

void Shader::setBool(const string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const string &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const string &name, float x, float y, float z,
                     float w) const {
  glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::setMat3(const string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::setMat4(const string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::checkCompileErrors(GLuint shader, string type) {
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
           << infoLog
           << "\n -- --------------------------------------------------- -- "
           << endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
           << infoLog
           << "\n -- --------------------------------------------------- -- "
           << endl;
    }
  }
}