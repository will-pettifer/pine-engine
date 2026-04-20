//
// Created by will-pettifer on 10/03/2026.
//

#include "MeshComponent.h"

#include "graphics/AssetManager.h"

MeshComponent::MeshComponent(string model, string shader) {
  name = "MeshComponent";
  modelPath = model;
  shaderPath = shader;
}

void MeshComponent::Render(glm::mat4 transform) {
  AssetManager::AddDrawCall({modelPath, shaderPath, transform});
}
