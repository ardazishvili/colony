#ifndef PLANT_H
#define PLANT_H

#include <glm/glm.hpp>

#include "../view/PlantView.h"

class Plant
{
public:
  Plant(Shader& shader, glm::vec3 position);
  void render();

private:
  PlantView _view;
};

#endif
