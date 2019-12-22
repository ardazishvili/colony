#include "TreeBuilder.h"
#include "Game.h"
#include "Tree.h"

TreeBuilder::TreeBuilder(Shader& shader,
                         Game* game,
                         Barrier& barrier,
                         Terrain* terrain) :
  AbstractPlantBuilder(shader, game, barrier, terrain)
{
}

void TreeBuilder::create()
{
  auto randomPos = generateUniformPosition();
  auto pos = _barrier.position();
  pos.x += randomPos.x;
  pos.y += randomPos.y;
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
