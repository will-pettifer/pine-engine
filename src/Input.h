//
// Created by will-pettifer on 01/05/2026.
//

#ifndef PINE_ENGINE_INPUT_H
#define PINE_ENGINE_INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

struct Input {
  GLFWwindow *window;
  glm::vec2 mouseMovement;
  float mouseScroll;
};

#endif // PINE_ENGINE_INPUT_H
