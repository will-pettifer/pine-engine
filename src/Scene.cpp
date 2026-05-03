//
// Created by will-pettifer on 10/03/2026.
//

#include "Scene.h"

#include "graphics/AssetManager.h"

#include <iostream>

Scene::Scene() {}

void Scene::Update(float delta, GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  Input input = {window, mouseMovement, mouseScroll};
  RecursiveUpdate(root, delta, &input);
  RecursiveDeleteQueue(root);
  RecursiveRender(root, glm::mat4(1.0f));

  mouseMovement = glm::vec2(0);
  mouseScroll = 0;
}

void Scene::ProcessMouseMovement(float xoffset, float yoffset) {
  mouseMovement.x += xoffset;
  mouseMovement.y += yoffset;
}

void Scene::ProcessMouseScroll(float yoffset) { mouseScroll += yoffset; }

void Scene::RecursiveUpdate(std::shared_ptr<Node> node, float delta,
                            Input *input) {
  node->Update(delta, input);
  for (auto &child : node->GetChildren()) {
    RecursiveUpdate(child, delta, input);
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