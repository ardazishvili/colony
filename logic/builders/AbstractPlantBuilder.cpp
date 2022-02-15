#include "logic/builders/AbstractPlantBuilder.h"

#include <chrono>
#include <functional>
#include <random>

AbstractPlantBuilder::AbstractPlantBuilder(Barrier& barrier,
                                           fig::Terrain& terrain)
    : AbstractUnitBuilder(), _barrier(barrier), _terrain(terrain) {}

glm::vec2 AbstractPlantBuilder::generateUniformPosition() const {
  std::mt19937 generator(
      std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<float> dReal(0, 2 * M_PI);
  auto getRandomAngle = std::bind(dReal, generator);
  auto randomAngle = getRandomAngle();
  // don't put plant closer than offset to barrier border
  auto offset = 0.1;
  auto randomR = getRandomAngle() * (_barrier.radius() - offset) / (2 * M_PI);

  return glm::vec2(randomR * ::cos(randomAngle), randomR * ::sin(randomAngle));
}
