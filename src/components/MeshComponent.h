//
// Created by will-pettifer on 10/03/2026.
//

#ifndef PINE_ENGINE_MESHCOMPONENT_H
#define PINE_ENGINE_MESHCOMPONENT_H
#include "../nodes/Node.h"

using namespace std;

class MeshComponent : public Node {
public:
  explicit MeshComponent(string model = "cube", string shader = "ps1");
  void Render(glm::mat4 transform) override;

private:
  string modelPath;
  string shaderPath;
};

#endif // PINE_ENGINE_MESHCOMPONENT_H