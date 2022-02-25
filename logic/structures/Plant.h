#pragma once

#include <glm/glm.hpp>

#include "logic/structures/AbstractPlant.h"
#include "view/PlantView.h"

class Plant : public AbstractPlant {
 public:
  Plant(glm::vec3 position);
};
