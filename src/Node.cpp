//
// Created by will-pettifer on 10/03/2026.
//

#include "Node.h"

#include "Scene.h"

#include <print>

Node::Node() {}

std::weak_ptr<Node> Node::GetParent() { return parent; }
void Node::SetParent(std::weak_ptr<Node> parent) { this->parent = parent; }

std::list<std::shared_ptr<Node>> Node::GetChildren() { return children; }
void Node::AddChild(std::shared_ptr<Node> child) {
  children.push_back(child);
  if (auto locked = child->GetParent().lock()) {
    locked->RemoveChild(child);
  }
  child->SetParent(weak_from_this());
  if (!child->hasEnteredTree) {
    child->hasEnteredTree = true;
    child->OnEnterTree();
  }
}
void Node::RemoveChild(std::shared_ptr<Node> child) {
  std::erase(children, child);
}

void Node::QueueDelete() {
  if (auto locked = parent.lock()) {
    locked->deleteQueue.push_back(shared_from_this());
  }
}

void Node::OnEnterTree() {}
void Node::Update(float delta) {}
void Node::DeleteQueue() {
  for (auto &child : deleteQueue) {
    RemoveChild(child);
    if (child.use_count() > 1) {
      std::printf("Trying to delete child with >1 strong ref!");
    }
  }
  deleteQueue.clear();
}

void Node::Input() {}
