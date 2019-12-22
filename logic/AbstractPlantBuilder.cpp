#include <functional>
#include <random>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "AbstractPlantBuilder.h"

AbstractPlantBuilder::AbstractPlantBuilder(Shader& shader,
                                           Game* game,
                                           Barrier& barrier,
                                           Terrain* terrain) :
  AbstractUnitBuilder(game),
  _shader(shader), _game(game), _barrier(barrier), _terrain(terrain)
{
}

glm::vec2 AbstractPlantBuilder::generateUniformPosition() const
{
  std::mt19937 generator(glfwGetTime() * 1000);
  std::uniform_real_distribution<float> dReal(0, 2 * M_PI);
  auto getRandomAngle = std::bind(dReal, generator);
  auto randomAngle = getRandomAngle();
  auto randomR = getRandomAngle() * _barrier.radius() / (2 * M_PI);

  return glm::vec2(randomR * ::cos(randomAngle), randomR * ::sin(randomAngle));
}
