//
// Created by will-pettifer on 02/04/2026.
//

#include "GameManager.h"

#include "Orbiter.h"
#include "SpinningCube.h"
#include "components/MeshComponent.h"

#include <iostream>

void GameManager::OnEnterTree() {
  for (int i = 0; i < 5; i++) {
    shared_ptr<Orbiter> object = make_shared<Orbiter>(0.1f);
    AddChild(object);
    object->AddChild(make_shared<MeshComponent>("cube"));
    for (int i = 0; i < 5; i++) {
      shared_ptr<Orbiter> satellite = make_shared<Orbiter>(0.5f);
      object->AddChild(satellite);
      satellite->AddChild(make_shared<MeshComponent>("cube"));
    }
  }
}
