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

class Node : public std::enable_shared_from_this<Node> {
public:
  Node();

  std::string name;

  glm::vec3 position = {0, 0, 0};
  glm::quat rotation = glm::quat(1, 0, 0, 0);
  glm::vec3 scale = {1, 1, 1};

  std::weak_ptr<Node> GetParent();
  void SetParent(std::weak_ptr<Node> parent);

  std::list<std::shared_ptr<Node>> GetChildren();
  void AddChild(std::shared_ptr<Node> child);
  void RemoveChild(std::shared_ptr<Node> child);

  void QueueDelete();

  void OnEnterTree();
  // Run every frame
  void Update(float delta);
  void DeleteQueue();

  void Input();

private:
  bool hasEnteredTree = false;

  std::weak_ptr<Node> parent;
  std::list<std::shared_ptr<Node>> children;
  std::list<std::shared_ptr<Node>> deleteQueue;
};

#endif // PINE_ENGINE_NODE_H