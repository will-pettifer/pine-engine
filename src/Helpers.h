//
// Created by will-pettifer on 02/04/2026.
//

#ifndef PINE_ENGINE_HELPERS_H
#define PINE_ENGINE_HELPERS_H
#include <random>

using namespace std;

class hlp {
public:
  static float RandFloat() {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rng);
  }
};

#endif // PINE_ENGINE_HELPERS_H
