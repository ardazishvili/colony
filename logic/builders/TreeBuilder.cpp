#include "TreeBuilder.h"

#include "logic/Game.h"
#include "logic/structures/Tree.h"

TreeBuilder::TreeBuilder(Barrier& barrier, fig::Terrain& terrain)
    : AbstractPlantBuilder(barrier, terrain) {}

void TreeBuilder::addToGame(Game& game) {
  auto randomPos = generateUniformPosition();
  auto pos = _barrier.position();
  pos.x += randomPos.x;
  pos.y += randomPos.y;
  pos.z = _terrain.getXYZ(glm::vec2(pos.x, pos.y)).z +
          fig::Terrain::SUBTERRAIN_OFFSET;
  auto tree = std::make_shared<Tree>(pos);

  _barrier.addPlant(tree);
  game.addPlant(tree);
}

fig::MenuTextures TreeBuilder::getPreviewType() {
  return fig::MenuTextures::Tree;
}
