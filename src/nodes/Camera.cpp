//
// Created by will-pettifer on 15/03/2026.
//

#include "../nodes/Camera.h"

#include <algorithm>

void Camera::Update(float delta, Input *input) {
  zoom -= input->mouseScroll;
  zoom = clamp(zoom, 1.0f, 45.0f);
}

glm::mat4 Camera::GetViewMatrix() {
  glm::vec3 globPos = GetGlobalPosition();
  glm::vec3 front = GetGlobalRotation() * glm::vec3(1, 0, 0);
  glm::vec3 right = glm::cross(front, {0, 1, 0});
  glm::vec3 up = glm::cross(right, front);
  return glm::lookAt(globPos, globPos + front, up);
}