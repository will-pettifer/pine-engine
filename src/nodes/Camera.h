//
// Created by will-pettifer on 15/03/2026.
//

#ifndef PINE_ENGINE_CAMERA_H
#define PINE_ENGINE_CAMERA_H

#include "Node.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera : public Node {
public:
  float zoom = 45;

  void Update(float delta, Input *input) override;

  glm::mat4 GetViewMatrix();
};

#endif // PINE_ENGINE_CAMERA_H
