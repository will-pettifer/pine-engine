//
// Created by will-pettifer on 10/03/2026.
//

#include "MeshComponent.h"

#include "graphics/AssetManager.h"

MeshComponent::MeshComponent(string model) {
  name = "MeshComponent";
  modelPath = model + "/" + model + ".obj";
}

void MeshComponent::Render(glm::mat4 transform) {
  AssetManager::AddDrawCall({modelPath, transform});
}
