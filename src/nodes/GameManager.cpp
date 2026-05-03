//
// Created by will-pettifer on 02/04/2026.
//

#include "nodes/GameManager.h"

#include "Orbiter.h"
#include "PlayerController.h"
#include "Scene.h"
#include "Skybox.h"
#include "../components/PointLight.h"
#include "SpinningCube.h"
#include "../components/MeshComponent.h"
#include "components/DirectionalLight.h"

#include <iostream>

void GameManager::OnEnterTree() {
  shared_ptr<PlayerController> player = make_shared<PlayerController>();
  AddChild(player);
  shared_ptr<Camera> camera = make_shared<Camera>();
  player->AddChild(camera);
  Scene::camera = camera;

  shared_ptr<Skybox> skybox = make_shared<Skybox>();
  AddChild(skybox);
  skybox->scale = glm::vec3(80);
  skybox->AddChild(make_shared<MeshComponent>("daybox", "ps1_unlit"));
  skybox->target = player;

  shared_ptr<DirectionalLight> dLight =
      make_shared<DirectionalLight>(glm::vec3(1, 0.85, 0.4), 0.9f);
  AddChild(dLight);
  dLight->rotation *=
      glm::angleAxis(glm::radians(45.0f), glm::vec3(-0.5f, 1.0f, 0.0f));

  shared_ptr<SpinningCube> cube = make_shared<SpinningCube>();
  AddChild(cube);
  cube->AddChild(make_shared<MeshComponent>());
  cube->position = glm::vec3(3, 0, 0);
  cube->scale = glm::vec3(0.8);

  shared_ptr<MeshComponent> spinningSphere =
      make_shared<MeshComponent>("glowing_orb");
  cube->AddChild(spinningSphere);
  spinningSphere->position = {0, -3, 0};

  shared_ptr<MeshComponent> platform = make_shared<MeshComponent>("platform");
  AddChild(platform);
  platform->position = glm::vec3(0, -5, 0);
  platform->scale = glm::vec3(0.3);

  shared_ptr<Orbiter> orbiter = make_shared<Orbiter>(-3, 7, 2);
  AddChild(orbiter);
  orbiter->AddChild(make_shared<PointLight>(glm::vec3(1, 1, 1), 1.5, 10));
  orbiter->AddChild(make_shared<MeshComponent>("glowing_orb", "ps1_unlit"));
}
