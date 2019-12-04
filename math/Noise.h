#ifndef NOISE_H
#define NOISE_H

#include <vector>

#include <glm/glm.hpp>

class Noise
{
public:
  Noise(unsigned int seed, unsigned int period);
  float eval(glm::vec2 p);

private:
  unsigned int _period;
  unsigned int _mask;
  std::vector<float> _r;
  std::vector<float> _pTable;
};

#endif
