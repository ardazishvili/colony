#ifndef PLANT_H
#define PLANT_H

#include <glm/glm.hpp>

#include "../view/PlantView.h"

class Plant
{
public:
  Plant(Shader& shader, glm::vec3 position);
  void render();
  glm::vec2 position();

private:
  PlantView _view;
  float _strenght{ 0.0f }; // percent
};

using Plants = std::vector<std::shared_ptr<Plant>>;

#endif
