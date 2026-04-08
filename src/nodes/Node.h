//
// Created by will-pettifer on 10/03/2026.
//

#ifndef PINE_ENGINE_NODE_H
#define PINE_ENGINE_NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <list>
#include <memory>
#include <string>

using namespace std;

class Node : public enable_shared_from_this<Node> {
public:
  Node();

  string name = "Node";

  glm::vec3 position = {0, 0, 0};
  glm::quat rotation = glm::quat(1, 0, 0, 0);
  glm::vec3 scale = {1, 1, 1};

  weak_ptr<Node> GetParent();
  void SetParent(weak_ptr<Node> parent);

  list<shared_ptr<Node>> GetChildren();
  void AddChild(shared_ptr<Node> child);
  void RemoveChild(shared_ptr<Node> child);

  void QueueDelete();

  virtual void OnEnterTree();
  virtual void Update(float delta);
  virtual void Render(glm::mat4 transform);
  virtual void Input();

  void DeleteQueue();

private:
  bool hasEnteredTree = false;

  weak_ptr<Node> parent;
  list<shared_ptr<Node>> children;
  list<shared_ptr<Node>> deleteQueue;
};

#endif // PINE_ENGINE_NODE_H