//
// Created by will-pettifer on 02/04/2026.
//

#include "nodes/GameManager.h"

#include "Orbiter.h"
#include "PointLight.h"
#include "SpinningCube.h"
#include "../components/MeshComponent.h"

#include <iostream>

void GameManager::OnEnterTree() {
  shared_ptr<PointLight> light = make_shared<PointLight>();
  AddChild(light);
  light->AddChild(make_shared<MeshComponent>("glowing_orb", "ps1"));

  shared_ptr<SpinningCube> cube = make_shared<SpinningCube>();
  AddChild(cube);
  cube->AddChild(make_shared<MeshComponent>());
  cube->position = glm::vec3(3, 0, 0);
  cube->scale = glm::vec3(0.8);

  shared_ptr<MeshComponent> cube1 = make_shared<MeshComponent>();
  AddChild(cube1);
  cube1->position = glm::vec3(5, 0, 0);
  cube1->scale = glm::vec3(0.8);

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
