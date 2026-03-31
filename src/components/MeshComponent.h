//
// Created by will-pettifer on 10/03/2026.
//

#ifndef PINE_ENGINE_MESHCOMPONENT_H
#define PINE_ENGINE_MESHCOMPONENT_H
#include "Node.h"

using namespace std;

class MeshComponent : public Node {
public:
  void Update(float delta);

private:
  string modelPath = "cube/cube.obj";
};

#endif // PINE_ENGINE_MESHCOMPONENT_H