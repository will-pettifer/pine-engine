//
// Created by will-pettifer on 02/04/2026.
//

#include "nodes/GameManager.h"

#include "Orbiter.h"
#include "../components/PointLight.h"
#include "SpinningCube.h"
#include "../components/MeshComponent.h"
#include "components/DirectionalLight.h"

#include <iostream>

void GameManager::OnEnterTree() {
  shared_ptr<DirectionalLight> dLight =
      make_shared<DirectionalLight>(glm::vec3(1, 0.85, 0.7), 0.9f);
  AddChild(dLight);
  dLight->rotation *=
      glm::angleAxis(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

  shared_ptr<PointLight> light = make_shared<PointLight>(glm::vec3(1, 1, 0), 1);
  AddChild(light);
  light->AddChild(make_shared<MeshComponent>("glowing_orb", "ps1_unlit"));

  shared_ptr<SpinningCube> cube = make_shared<SpinningCube>();
  AddChild(cube);
  cube->AddChild(make_shared<MeshComponent>());
  cube->position = glm::vec3(3, 0, 0);
  cube->scale = glm::vec3(0.8);

  shared_ptr<MeshComponent> spinningSphere =
      make_shared<MeshComponent>("glowing_orb");
  cube->AddChild(spinningSphere);
  spinningSphere->position = {0, -3, 0};

  shared_ptr<MeshComponent> cube1 = make_shared<MeshComponent>("ship");
  AddChild(cube1);
  cube1->position = glm::vec3(5, 0, 0);
  cube1->scale = glm::vec3(0.8);

  shared_ptr<MeshComponent> platform = make_shared<MeshComponent>("platform");
  AddChild(platform);
  platform->position = glm::vec3(0, -10, 0);
  platform->scale = glm::vec3(0.5);

  for (int i = 0; i < 5; i++) {
    shared_ptr<Orbiter> object = make_shared<Orbiter>(0.4f);
    AddChild(object);
    object->AddChild(make_shared<MeshComponent>());
    for (int i = 0; i < 5; i++) {
      shared_ptr<Orbiter> satellite = make_shared<Orbiter>(0.5f);
      object->AddChild(satellite);
      satellite->AddChild(make_shared<MeshComponent>());
    }
  }
}
