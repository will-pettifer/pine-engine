//
// Created by will-pettifer on 10/03/2026.
//

#ifndef PINE_ENGINE_SCENE_H
#define PINE_ENGINE_SCENE_H

#include <list>
#include <memory>

#include "Node.h"

#include <GLFW/glfw3.h>

class Scene {
private:
  void RecursiveInput(GLFWwindow *window, std::shared_ptr<Node> node);
  void RecursiveUpdate(float delta, std::shared_ptr<Node> node);
  void RecursiveDeleteQueue(std::shared_ptr<Node> node);
  void RecursiveRender(std::shared_ptr<Node> node);

public:
  std::shared_ptr<Node> root;

  void Update(float delta, GLFWwindow *window);
};

#endif // PINE_ENGINE_SCENE_H