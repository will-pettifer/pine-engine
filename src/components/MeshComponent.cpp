//
// Created by will-pettifer on 10/03/2026.
//

#include "MeshComponent.h"

#include "graphics/AssetManager.h"

void MeshComponent::Update(float delta) {
  glm::mat4 t = glm::translate(glm::mat4(1.0f), position);
  glm::mat4 r = glm::mat4_cast(rotation);
  glm::mat4 s = glm::scale(glm::mat4(1.0f), scale);
  glm::mat4 transform = t * r * s;

  AssetManager::AddDrawCall({modelPath, transform});
}