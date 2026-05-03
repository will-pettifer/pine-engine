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
  float height;
  float radius;
  float speed;

  Orbiter(float height, float radius, float speed) {
    this->height = height;
    this->radius = radius;
    this->speed = speed;
    age = hlp::RandFloat() * numbers::pi * 2;
  }

  void Update(float delta, Input *input) override {
    age += delta * speed;
    position = glm::vec3{cos(age) * radius, height, sin(age) * radius};
  }
};

#endif // PINE_ENGINE_ORBITER_H
