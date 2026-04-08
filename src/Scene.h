//
// Created by will-pettifer on 10/03/2026.
//

#ifndef PINE_ENGINE_SCENE_H
#define PINE_ENGINE_SCENE_H

#include "graphics/Camera.h"

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "nodes/Node.h"

using namespace std;

class Scene {
public:
  Scene();

  shared_ptr<Node> root = make_shared<Node>();
  Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));


  void Update(float delta, GLFWwindow *window);

private:
  void RecursiveInput(GLFWwindow *window, shared_ptr<Node> node);
  void RecursiveUpdate(float delta, shared_ptr<Node> node);
  void RecursiveDeleteQueue(shared_ptr<Node> node);
  void RecursiveRender(shared_ptr<Node> node, glm::mat4 transform);
};

#endif // PINE_ENGINE_SCENE_H