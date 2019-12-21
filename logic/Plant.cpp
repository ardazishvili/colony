#include "Plant.h"

Plant::Plant(Shader& shader, glm::vec3 position) :
  AbstractPlant(std::make_unique<PlantView>(shader, position))
{
}
