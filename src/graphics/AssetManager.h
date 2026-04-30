//
// Created by will-pettifer on 11/03/2026.
//

#ifndef PINE_ENGINE_ASSETMANAGER_H
#define PINE_ENGINE_ASSETMANAGER_H

#include "Camera.h"
#include "Model.h"
#include "Shader.h"

#include <memory>
#include <optional>
#include <string>

using namespace std;

class AssetManager {
public:
  static void Init(Camera *cam, float scrWidth, float scrHeight);

  struct DirectionalLight {
    glm::vec3 colour;
    glm::vec3 direction;
    float intensity;
  };

  struct PointLight {
    glm::vec3 colour;
    glm::vec3 position;
    float radius;
    float intensity;
  };

  struct DrawCall {
    string modelPath;
    string shaderPath;
    glm::mat4 transform;
  };

  static void AddDirectionalLight(DirectionalLight dLight);
  static void AddPointLight(PointLight pointLight);
  static void AddDrawCall(DrawCall drawCall);
  static void Draw();
  static shared_ptr<Shader> FindShader(string path);
  static shared_ptr<Model> FindModel(string path);

private:
  static inline glm::vec2 screen;
  static inline Camera *camera = nullptr;
  static inline optional<DirectionalLight> directionalLight;
  static inline vector<PointLight> pointLights;
  static inline vector<DrawCall> drawCalls;
  static inline unordered_map<string, shared_ptr<Shader>> shaderCache;
  static inline unordered_map<string, shared_ptr<Model>> modelCache;
};

#endif // PINE_ENGINE_ASSETMANAGER_H
