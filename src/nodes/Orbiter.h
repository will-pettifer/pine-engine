//
// Created by will-pettifer on 08/04/2026.
//

#ifndef PINE_ENGINE_ORBITER_H
#define PINE_ENGINE_ORBITER_H
#include "Helpers.h"
#include "Node.h"

using namespace std;

class Orbiter : public Node {
public:
  float age;
  float size;
  float orbitalDistance;

  Orbiter(float size) {
    this->size = size;
    age = hlp::RandFloat() * numbers::pi * 2;
    orbitalDistance = hlp::RandFloat() * size * 5 + 1;
    scale = glm::vec3{size};
  }

  void Update(float delta) override {
    age += delta;
    position =
        glm::vec3{cos(age / orbitalDistance), sin(age / orbitalDistance), 0} *
        orbitalDistance;
  }
};

#endif // PINE_ENGINE_ORBITER_H
