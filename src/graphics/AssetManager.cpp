//
// Created by will-pettifer on 11/03/2026.
//

#include "AssetManager.h"

#include "Model.h"

#include <algorithm>

void AssetManager::Init(Camera *cam, float scrWidth, float scrHeight) {
  screen = {scrWidth, scrHeight};
  camera = cam;
  FindShader("default");
}

void AssetManager::AddDrawCall(DrawCall drawCall) {
  drawCalls.push_back(drawCall);
}

void AssetManager::Draw() {
  ranges::sort(drawCalls, [](const DrawCall &a, const DrawCall &b) {
    if (a.shaderPath != b.shaderPath)
      return a.shaderPath < b.shaderPath;
    if (a.modelPath != b.modelPath)
      return a.modelPath < b.modelPath;
    return false;
  });

  glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom),
                                          screen.x / screen.y, 0.1f, 100.0f);
  glm::mat4 view = camera->GetViewMatrix();

  string lastShader, lastModel;
  shared_ptr<Shader> shader;
  shared_ptr<Model> model;

  for (const auto &drawCall : drawCalls) {
    if (drawCall.shaderPath != lastShader) {
      lastShader = drawCall.shaderPath;
      shader = FindShader(drawCall.shaderPath);
      shader->Use();

      shader->setMat4("projection", projection);
      shader->setMat4("view", view);
    }

    if (drawCall.modelPath != lastModel) {
      lastModel = drawCall.modelPath;
      model = FindModel(drawCall.modelPath);
    }

    shader->setMat4("model", drawCall.transform);
    model->Draw(*shader);
  }

  drawCalls.clear();
}

shared_ptr<Shader> AssetManager::FindShader(string path) {
  auto it = shaderCache.find(path);
  if (it != shaderCache.end())
    return it->second;

  string fullPath = "assets/shaders/" + path;
  shared_ptr<Shader> shader = make_shared<Shader>();
  shader->Init((fullPath + "_v.glsl").c_str(), (fullPath + "_f.glsl").c_str());

  return shaderCache.emplace(path, shader).first->second;
}

shared_ptr<Model> AssetManager::FindModel(string path) {
  auto it = modelCache.find(path);
  if (it != modelCache.end())
    return it->second;

  return modelCache
      .emplace(path, make_shared<Model>(path + "/" + path + ".obj"))
      .first->second;
}
