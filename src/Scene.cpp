//
// Created by will-pettifer on 10/03/2026.
//

#include "Scene.h"

#include "graphics/AssetManager.h"

#include <iostream>

Scene::Scene() {}

void Scene::Update(float delta, GLFWwindow *window) {
  // ===[ Inputs ]===
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, delta);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, delta);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, delta);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, delta);
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    camera.ProcessKeyboard(UP, delta);
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    camera.ProcessKeyboard(DOWN, delta);

  RecursiveInput(window, root);
  RecursiveUpdate(delta, root);
  RecursiveDeleteQueue(root);
  RecursiveRender(root, glm::mat4(1.0f));
}

void Scene::RecursiveInput(GLFWwindow *window, std::shared_ptr<Node> node) {
  for (auto &child : node->GetChildren()) {
    RecursiveInput(window, child);
  }
  // Process input
}

void Scene::RecursiveUpdate(float delta, std::shared_ptr<Node> node) {
  node->Update(delta);
  for (auto &child : node->GetChildren()) {
    RecursiveUpdate(delta, child);
  }
}

void Scene::RecursiveDeleteQueue(std::shared_ptr<Node> node) {
  node->DeleteQueue();
  for (auto &child : node->GetChildren()) {
    RecursiveDeleteQueue(child);
  }
}

void Scene::RecursiveRender(std::shared_ptr<Node> node, glm::mat4 transform) {
  glm::mat4 t = glm::translate(glm::mat4(1.0f), node->position);
  glm::mat4 r = glm::mat4_cast(node->rotation);
  glm::mat4 s = glm::scale(glm::mat4(1.0f), node->scale);
  transform = transform * t * r * s;
  node->Render(transform);

  for (auto &child : node->GetChildren()) {
    RecursiveRender(child, transform);
  }
}