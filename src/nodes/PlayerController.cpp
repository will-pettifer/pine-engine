//
// Created by will-pettifer on 01/05/2026.
//

#include "PlayerController.h"

#include "Helpers.h"

#include <algorithm>
#include <iostream>

void PlayerController::Update(float delta, Input *input) {
  // ==[ Orientation ]==
  glm::vec2 mouseMovement = input->mouseMovement * lookSensitivity;
  yaw -= mouseMovement.x;
  pitch += mouseMovement.y;
  pitch = clamp(pitch, -89.0f, 89.0f);

  rotation = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0)) *
             glm::angleAxis(glm::radians(pitch), glm::vec3(0, 0, 1));

  // ==[ Translation ]==
  glm::vec3 direction = glm::vec3(0);
  glm::vec3 forward = glm::vec3(1, 0, 0);
  glm::vec3 right = glm::vec3(0, 0, 1);
  glm::vec3 worldUp = glm::vec3(0, 1, 0);
  forward = rotation * forward;
  right = rotation * right;
  forward.y = 0;
  right.y = 0;

  if (glfwGetKey(input->window, GLFW_KEY_W) == GLFW_PRESS)
    direction += forward;
  if (glfwGetKey(input->window, GLFW_KEY_A) == GLFW_PRESS)
    direction -= right;
  if (glfwGetKey(input->window, GLFW_KEY_S) == GLFW_PRESS)
    direction -= forward;
  if (glfwGetKey(input->window, GLFW_KEY_D) == GLFW_PRESS)
    direction += right;
  if (glfwGetKey(input->window, GLFW_KEY_Q) == GLFW_PRESS)
    direction -= worldUp;
  if (glfwGetKey(input->window, GLFW_KEY_E) == GLFW_PRESS)
    direction += worldUp;

  direction = hlp::Normalise(direction);
  position += direction * delta * movementSpeed;
}
