//
// Created by will-pettifer on 11/03/2026.
//

#include "AssetManager.h"

#include "Model.h"

#include <algorithm>

void AssetManager::Init(Camera *cam, float scrWidth, float scrHeight) {
  screen = {scrWidth, scrHeight};
  camera = cam;
  shader.Init("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");
}

void AssetManager::AddDrawCall(DrawCall drawCall) {
  drawCalls.push_back(drawCall);
}

void AssetManager::Draw() {
  shader.use();

  glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom),
                                          screen.x / screen.y, 0.1f, 100.0f);
  glm::mat4 view = camera->GetViewMatrix();
  shader.setMat4("projection", projection);
  shader.setMat4("view", view);

  ranges::sort(drawCalls, {}, &DrawCall::modelPath);

  string lastPath;
  weak_ptr<Model> model;
  for (const auto &drawCall : drawCalls) {
    if (drawCall.modelPath != lastPath) {
      lastPath = drawCall.modelPath;
      model = FindModel(drawCall.modelPath);
    }

    shader.setMat4("model", drawCall.transform);
    if (auto mod = model.lock())
      mod->Draw(shader);
  }

  drawCalls.clear();
}

weak_ptr<Model> AssetManager::FindModel(string path) {
  auto it = modelCache.find(path);
  if (it != modelCache.end())
    return it->second;

  return modelCache.emplace(path, make_shared<Model>(path)).first->second;
}
