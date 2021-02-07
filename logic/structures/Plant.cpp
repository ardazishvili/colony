#include "Plant.h"

Plant::Plant(fig::Shader& shader, glm::vec3 position) : AbstractPlant(std::make_unique<PlantView>(shader, position))
{
}
