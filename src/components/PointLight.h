//
// Created by will-pettifer on 08/04/2026.
//

#ifndef PINE_ENGINE_POINTLIGHT_H
#define PINE_ENGINE_POINTLIGHT_H
#include "../nodes/Node.h"
#include "graphics/AssetManager.h"

class PointLight : public Node {
public:
  glm::vec3 colour;
  float intensity;
  float radius;

  PointLight(glm::vec3 colour = {1, 1, 1}, float intensity = 1,
             float radius = 5) {
    this->colour = colour;
    this->intensity = intensity;
    this->radius = radius;
  }

  void Render(glm::mat4 transform) override {
    AssetManager::AddPointLight({colour, position, radius, intensity});
  }
};

#endif // PINE_ENGINE_POINTLIGHT_H
