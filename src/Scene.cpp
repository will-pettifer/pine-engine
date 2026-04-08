//
// Created by will-pettifer on 10/03/2026.
//

#include "Scene.h"

#include "graphics/AssetManager.h"

#include <iostream>

Scene::Scene() {}

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

void Scene::Update(float delta, GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  RecursiveInput(window, root);
  RecursiveUpdate(delta, root);
  RecursiveDeleteQueue(root);
  RecursiveRender(root, glm::mat4(1.0f));
}
