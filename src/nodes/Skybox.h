//
// Created by will-pettifer on 30/04/2026.
//

#ifndef PINE_ENGINE_SKYBOX_H
#define PINE_ENGINE_SKYBOX_H
#include "Node.h"

class Skybox : public Node {
public:
  weak_ptr<Node> target;

  void Update(float delta, Input *input) override {
    if (auto t = target.lock()) {
      position = t->position;
    }
  }
};

#endif // PINE_ENGINE_SKYBOX_H
