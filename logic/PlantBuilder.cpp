#include <functional>
#include <random>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "Game.h"
#include "PlantBuilder.h"

PlantBuilder::PlantBuilder(Shader& shader, Game& game, Barrier& barrier) :
  _shader(shader), _game(game), _barrier(barrier)
{}

void PlantBuilder::create()
{
  std::mt19937 generator(glfwGetTime() * 1000);
  std::uniform_real_distribution<float> dReal(0, 2 * M_PI);
  auto getRandomAngle = std::bind(dReal, generator);
  auto randomAngle = getRandomAngle();
  auto randomR = getRandomAngle() / (2 * M_PI);
  std::cout << "randomAngle= " << randomAngle << std::endl;

  auto x = randomR * ::cos(randomAngle);
  auto y = randomR * ::sin(randomAngle);
  auto pos = _barrier.position();
  pos.x += x;
  pos.y += y;
  pos.z += 0.5;
  auto plant = std::make_shared<Plant>(_shader, pos);

  _game.addPlant(plant);
}

MenuTextures PlantBuilder::getPreviewType()
{
  return MenuTextures::Plant;
}
