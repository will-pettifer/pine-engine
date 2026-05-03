//
// Created by will-pettifer on 10/03/2026.
//

#ifndef PINE_ENGINE_SCENE_H
#define PINE_ENGINE_SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "nodes/Camera.h"
#include <memory>
#include "nodes/Node.h"

using namespace std;

class Scene {
public:
  Scene();

  shared_ptr<Node> root = make_shared<Node>();
  inline static shared_ptr<Camera> camera = make_shared<Camera>();

  void Update(float delta, GLFWwindow *window);

  void ProcessMouseMovement(float xoffset, float yoffset);

  void ProcessMouseScroll(float yoffset);

private:
  glm::vec2 mouseMovement = glm::vec2(0);
  float mouseScroll = 0;

  void RecursiveUpdate(std::shared_ptr<Node> node, float delta, Input *input);
  void RecursiveDeleteQueue(shared_ptr<Node> node);
  void RecursiveRender(shared_ptr<Node> node, glm::mat4 transform);
};

#endif // PINE_ENGINE_SCENE_H