#include <functional>
#include <iostream>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "Noise.h"

float smoothstep(float t)
{
  return t * t * (3 - 2 * t);
}

float smoothstepDeriv(float t)
{
  return 6 * t * (1 - t);
}

Noise::Noise(unsigned int seed) : _mask(PERIOD - 1)
{
  std::mt19937 generator(seed);
  std::uniform_real_distribution<float> dReal(0, 2 * M_PI);
  auto getRandomAngle = std::bind(dReal, generator);

  for (unsigned int i = 0; i < PERIOD; ++i) {
    float phi = getRandomAngle();
    _gradients[i] = glm::vec2(::cos(phi), ::sin(phi));
    _gradients[i] = glm::normalize(_gradients[i]);
    _pTable[i] = i;
  }

  std::uniform_int_distribution<unsigned int> dInt;
  auto getRandomInt = std::bind(dInt, generator);
  for (unsigned int i = 0; i < PERIOD; ++i) {
    auto randomMappedInt = getRandomInt() & _mask;
    std::swap(_pTable[i], _pTable[randomMappedInt]);
    _pTable[i + PERIOD] = _pTable[i];
  }
}

float Noise::eval(glm::vec2 p, glm::vec2& derivs)
{
  int xi = std::floor(p.x);
  float deltaX = p.x - xi;
  float u = smoothstep(deltaX);
  float du = smoothstepDeriv(deltaX);

  int yi = std::floor(p.y);
  float deltaY = p.y - yi;
  float v = smoothstep(deltaY);
  float dv = smoothstepDeriv(deltaY);

  int x0 = xi & _mask;
  int x1 = (x0 + 1) & _mask;
  int y0 = yi & _mask;
  int y1 = (y0 + 1) & _mask;

  auto& cell_00 = _gradients[_pTable[_pTable[x0] + y0]];
  auto& cell_01 = _gradients[_pTable[_pTable[x0] + y1]];
  auto& cell_10 = _gradients[_pTable[_pTable[x1] + y0]];
  auto& cell_11 = _gradients[_pTable[_pTable[x1] + y1]];

  auto p00 = glm::vec2(deltaX, deltaY);
  auto p01 = glm::vec2(deltaX, deltaY - 1);
  auto p10 = glm::vec2(deltaX - 1, deltaY);
  auto p11 = glm::vec2(deltaX - 1, deltaY - 1);

  auto a = glm::dot(cell_00, p00);
  auto b = glm::dot(cell_10, p10);
  auto c = glm::dot(cell_01, p01);
  auto d = glm::dot(cell_11, p11);

  float k0 = b - a;
  float k1 = c - a;
  float k2 = a + d - b - c;

  derivs.x = du * k0 + du * v * k2;
  derivs.y = dv * k1 + u * dv * k2;

  return a + u * k0 + v * k1 + u * v * k2;
}

float Noise::fractal(glm::vec2 p,
                     glm::vec2& derivs,
                     float frequency,
                     float frequencyFactor,
                     float amplitudeFactor,
                     unsigned int numLayers)
{
  derivs = glm::vec2(0.0f, 0.0f);
  auto res = 0.0f;
  auto fp = p * frequency;
  float amplitude = 1.0f;
  for (unsigned int l = 0; l < numLayers; ++l) {
    glm::vec2 d(0.0f);
    res += eval(fp, d) * amplitude;
    derivs += d;
    fp *= frequencyFactor;
    amplitude *= amplitudeFactor;
  }

  /* derivs = glm::normalize(derivs); */
  return res;
}
