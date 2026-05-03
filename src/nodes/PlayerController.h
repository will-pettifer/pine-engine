//
// Created by will-pettifer on 01/05/2026.
//

#ifndef PINE_ENGINE_PLAYERCONTROLLER_H
#define PINE_ENGINE_PLAYERCONTROLLER_H
#include "Node.h"

class PlayerController : public Node {
public:
  void Update(float delta, Input *input) override;

private:
  float yaw = 0;
  float pitch = 0;
  float movementSpeed = 5;
  float lookSensitivity = 0.07;
};

#endif // PINE_ENGINE_PLAYERCONTROLLER_H
