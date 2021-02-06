#include "TreeBuilder.h"
#include "Game.h"
#include "Tree.h"

TreeBuilder::TreeBuilder(fig::Shader& shader, Game* game, Barrier& barrier, fig::Terrain* terrain) :
  AbstractPlantBuilder(shader, game, barrier, terrain)
{
}

void TreeBuilder::create()
{
  auto randomPos = generateUniformPosition();
  auto pos = _barrier.position();
  pos.x += randomPos.x;
  pos.y += randomPos.y;
  pos.z = _terrain->getXYZ(glm::vec2(pos.x, pos.y)).z + fig::Terrain::SUBTERRAIN_OFFSET;
  auto tree = std::make_shared<Tree>(_shader, pos);

  _barrier.addPlant(tree);
  _game->addPlant(tree);
}

fig::MenuTextures TreeBuilder::getPreviewType()
{
  return fig::MenuTextures::Tree;
}
