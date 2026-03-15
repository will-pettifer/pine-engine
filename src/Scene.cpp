//
// Created by will-pettifer on 10/03/2026.
//

#include "Scene.h"

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
void Scene::RecursiveRender(std::shared_ptr<Node> node) {
  for (auto &child : node->GetChildren()) {
    RecursiveRender(child);
  }
}

void Scene::Update(float delta, GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  RecursiveInput(window, root);
  RecursiveUpdate(delta, root);
  RecursiveDeleteQueue(root);
  RecursiveRender(root);
}
