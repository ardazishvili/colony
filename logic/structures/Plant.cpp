#include "Plant.h"

Plant::Plant(glm::vec3 position) : AbstractPlant(std::make_unique<PlantView>(position))
{
}
