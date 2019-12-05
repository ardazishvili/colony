#include <functional>
#include <iostream>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "Noise.h"

float gradientDot(uint8_t perm, glm::vec2 p)
{
  switch (perm & 3) {
    case 0:
      return p.x + p.y;
    case 1:
      return -p.x + p.y;
    case 2:
      return p.x - p.y;
    case 3:
      return -p.x - p.y;
    default:
      assert(0);
      return 0;
  }
}

float quintic(float t)
{
  return 6 * ::pow(t, 5) - 15 * ::pow(t, 4) + 10 * ::pow(t, 3);
}

float quinticDeriv(float t)
{
  return 30 * ::pow(t, 4) - 60 * ::pow(t, 3) + 30 * ::pow(t, 2);
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
  float u = quintic(deltaX);
  float du = quinticDeriv(deltaX);

  int yi = std::floor(p.y);
  float deltaY = p.y - yi;
  float v = quintic(deltaY);
  float dv = quinticDeriv(deltaY);

  int x0 = xi & _mask;
  int x1 = (x0 + 1) & _mask;
  int y0 = yi & _mask;
  int y1 = (y0 + 1) & _mask;

  auto p00 = glm::vec2(deltaX, deltaY);
  auto p01 = glm::vec2(deltaX, deltaY - 1);
  auto p10 = glm::vec2(deltaX - 1, deltaY);
  auto p11 = glm::vec2(deltaX - 1, deltaY - 1);

  auto a = gradientDot(hash(x0, y0), p00);
  auto b = gradientDot(hash(x0, y1), p10);
  auto c = gradientDot(hash(x1, y0), p01);
  auto d = gradientDot(hash(x1, y1), p11);

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

uint8_t Noise::hash(const int& x, const int& y) const
{
  return _pTable[_pTable[x] + y];
}
