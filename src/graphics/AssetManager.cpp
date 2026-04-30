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

void AssetManager::AddDirectionalLight(DirectionalLight dLight) {
  directionalLight = dLight;
}

void AssetManager::AddPointLight(PointLight pointLight) {
  pointLights.push_back(pointLight);
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

      shader->setVec3("ambientLight", ambientLight);
      shader->setBool("dLight.enabled", directionalLight.has_value());
      if (directionalLight.has_value()) {
        shader->setVec3("dLight.direction", directionalLight->direction);
        shader->setVec3("dLight.colour", directionalLight->colour);
        shader->setFloat("dLight.intensity", directionalLight->intensity);
      }

      shader->setInt("numPLights", (int)pointLights.size());
      for (int i = 0; i < (int)pointLights.size(); i++) {
        string base = "pointLights[" + to_string(i) + "]";
        shader->setVec3(base + ".colour", pointLights[i].colour);
        shader->setVec3(base + ".position", pointLights[i].position);
        shader->setFloat(base + ".radius", pointLights[i].radius);
        shader->setFloat(base + ".innerRadius", pointLights[i].innerRadius);
        shader->setFloat(base + ".intensity", pointLights[i].intensity);
      }
    }

    if (drawCall.modelPath != lastModel) {
      lastModel = drawCall.modelPath;
      model = FindModel(drawCall.modelPath);
    }

    shader->setMat4("model", drawCall.transform);
    model->Draw(*shader);
  }

  directionalLight.reset();
  pointLights.clear();
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

  return modelCache.emplace(path, make_shared<Model>(path + ".obj"))
      .first->second;
}
