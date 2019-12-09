#ifndef BARRIER_H
#define BARRIER_H

#include <glm/glm.hpp>

#include "../engine/Terrain.h"
#include "../view/BarrierView.h"

class Barrier
{
public:
  Barrier(Shader& textureShader, Shader& colorShader, glm::vec3 position);
  void render();
  void assignVertices(Terrain* terrain);

private:
  BarrierView _view;
  std::vector<unsigned int> _vertices;
  float _radius{ 1.0f };
};

#endif
