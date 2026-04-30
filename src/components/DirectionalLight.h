//
// Created by will-pettifer on 30/04/2026.
//

#ifndef PINE_ENGINE_DIRECTIONALLIGHT_H
#define PINE_ENGINE_DIRECTIONALLIGHT_H
#include "graphics/AssetManager.h"
#include "nodes/Node.h"

class DirectionalLight : public Node {
public:
  glm::vec3 colour;
  float intensity;

  DirectionalLight(glm::vec3 colour = {1, 1, 1}, float intensity = 1) {
    this->colour = colour;
    this->intensity = intensity;
  }

  void Render(glm::mat4 transform) override {
    AssetManager::AddDirectionalLight(
        {colour, rotation * glm::vec3(0.0f, 0.0f, -1.0f), intensity});
  }
};

#endif // PINE_ENGINE_DIRECTIONALLIGHT_H
