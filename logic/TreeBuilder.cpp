#include <functional>
#include <random>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "Game.h"
#include "Tree.h"
#include "TreeBuilder.h"

TreeBuilder::TreeBuilder(Shader& shader,
                         Game* game,
                         Barrier& barrier,
                         Terrain* terrain) :
  AbstractUnitBuilder(game),
  _shader(shader), _game(game), _barrier(barrier), _terrain(terrain)
{
}

void TreeBuilder::create()
{
  std::mt19937 generator(glfwGetTime() * 1000);
  std::uniform_real_distribution<float> dReal(0, 2 * M_PI);
  auto getRandomAngle = std::bind(dReal, generator);
  auto randomAngle = getRandomAngle();
  auto randomR = getRandomAngle() / (2 * M_PI);

  auto x = randomR * ::cos(randomAngle);
  auto y = randomR * ::sin(randomAngle);
  auto pos = _barrier.position();
  pos.x += x;
  pos.y += y;
  // TODO subterrain offset
  pos.z = _terrain->getXYZ(glm::vec2(pos.x, pos.y)).z + 0.3;
  auto tree = std::make_shared<Tree>(_shader, pos);

  _barrier.addPlant(tree);
  _game->addPlant(tree);
}

MenuTextures TreeBuilder::getPreviewType()
{
  return MenuTextures::Tree;
}
