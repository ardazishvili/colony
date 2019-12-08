#ifndef BARRIER_H
#define BARRIER_H

#include <glm/glm.hpp>

#include "../view/BarrierView.h"

class Barrier
{
public:
  Barrier(Shader& shader, glm::vec3 position);
  void render();

private:
  BarrierView _view;
};

#endif
