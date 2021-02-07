#ifndef PLANT_H
#define PLANT_H

#include <glm/glm.hpp>

#include "../../view/PlantView.h"
#include "AbstractPlant.h"

class Plant : public AbstractPlant
{
public:
  Plant(fig::Shader& shader, glm::vec3 position);
};

#endif
