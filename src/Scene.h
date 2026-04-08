//
// Created by will-pettifer on 10/03/2026.
//

#ifndef PINE_ENGINE_SCENE_H
#define PINE_ENGINE_SCENE_H

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "nodes/Node.h"

using namespace std;

class Scene {
private:
  void RecursiveInput(GLFWwindow *window, shared_ptr<Node> node);
  void RecursiveUpdate(float delta, shared_ptr<Node> node);
  void RecursiveDeleteQueue(shared_ptr<Node> node);
  void RecursiveRender(shared_ptr<Node> node, glm::mat4 transform);

public:
  Scene();

  shared_ptr<Node> root = make_shared<Node>();

  void Update(float delta, GLFWwindow *window);
};

#endif // PINE_ENGINE_SCENE_H