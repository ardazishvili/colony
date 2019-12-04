#include <functional>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "Noise.h"

float smoothstep(float t)
{
  return t * t * (3 - 2 * t);
}

Noise::Noise(unsigned int seed) : _mask(PERIOD - 1)
{
  std::mt19937 generator(seed);
  std::uniform_real_distribution<float> dReal;
  auto getRandomReal = std::bind(dReal, generator);

  for (unsigned int i = 0; i < PERIOD; ++i) {
    _r[i] = getRandomReal();
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

float Noise::eval(glm::vec2 p)
{
  int xi = std::floor(p.x);
  float deltaX = p.x - xi;
  float smoothedDeltaX = smoothstep(deltaX);

  int yi = std::floor(p.y);
  float deltaY = p.y - yi;
  float smoothedDeltaY = smoothstep(deltaY);

  int x0 = xi & _mask;
  int x1 = (x0 + 1) & _mask;
  int y0 = yi & _mask;
  int y1 = (y0 + 1) & _mask;

  auto& cell_00 = _r[_pTable[_pTable[x0] + y0]];
  auto& cell_01 = _r[_pTable[_pTable[x0] + y1]];
  auto& cell_10 = _r[_pTable[_pTable[x1] + y0]];
  auto& cell_11 = _r[_pTable[_pTable[x1] + y1]];

  auto xInterpolated0 = glm::lerp(cell_00, cell_10, smoothedDeltaX);
  auto xInterpolated1 = glm::lerp(cell_01, cell_11, smoothedDeltaX);

  auto yInterpolated =
    glm::lerp(xInterpolated0, xInterpolated1, smoothedDeltaY);
  return yInterpolated;
}

float Noise::fractal(glm::vec2 p,
                     float frequency,
                     float frequencyFactor,
                     float amplitudeFactor,
                     unsigned int numLayers)
{
  auto res = 0.0f;
  auto fp = p * frequency;
  float amplitude = 1.0f;
  for (unsigned int l = 0; l < numLayers; ++l) {
    res += eval(fp) * amplitude;
    fp *= frequencyFactor;
    amplitude *= amplitudeFactor;
  }

  return res;
}
