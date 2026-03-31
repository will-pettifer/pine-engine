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
#include <glm/glm.hpp>
#include <string>

using namespace std;

class AssetManager {
public:
  static void Init(Camera *cam, float scrWidth, float scrHeight);

  struct DrawCall {
    string modelPath;
    glm::mat4 transform;
  };

  static void AddDrawCall(DrawCall drawCall);
  static void Draw();
  static weak_ptr<Model> FindModel(string path);

private:
  static inline glm::vec2 screen;
  static inline Shader shader;
  static inline Camera *camera = nullptr;
  static inline vector<DrawCall> drawCalls;
  static inline unordered_map<string, shared_ptr<Model>> modelCache;
};

#endif // PINE_ENGINE_ASSETMANAGER_H
