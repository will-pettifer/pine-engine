//
// Created by will-pettifer on 02/04/2026.
//

#ifndef PINE_ENGINE_SPINNINGCUBE_H
#define PINE_ENGINE_SPINNINGCUBE_H
#include "Helpers.h"
#include "Node.h"

using namespace std;

class SpinningCube : public Node {
public:
  glm::vec3 direction;
  float speed;
  float rotationSpeed;

  void OnEnterTree() override {
    direction = {hlp::RandFloat(), hlp::RandFloat(), hlp::RandFloat()};
    direction -= glm::vec3(0.5f);
    direction = normalize(direction);
    speed = hlp::RandFloat() * 5;
    rotationSpeed = hlp::RandFloat() * 5;
  }

  void Update(float delta) override {
    position += direction * delta * speed;
    rotation *= glm::angleAxis(delta * rotationSpeed, glm::vec3{0, 1, 0});
  }
};

#endif // PINE_ENGINE_SPINNINGCUBE_H
