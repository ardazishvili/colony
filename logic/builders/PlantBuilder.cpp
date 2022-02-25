#include "PlantBuilder.h"

#include "logic/Game.h"
#include "logic/structures/Plant.h"

PlantBuilder::PlantBuilder(Barrier& barrier, fig::Terrain& terrain)
    : AbstractPlantBuilder(barrier, terrain) {}

void PlantBuilder::addToGame(Game& game) {
  auto randomPos = generateUniformPosition();
  auto pos = _barrier.position();
  pos.x += randomPos.x;
  pos.y += randomPos.y;
  pos.z = _terrain.getXYZ(glm::vec2(pos.x, pos.y)).z +
          fig::Terrain::SUBTERRAIN_OFFSET;
  auto plant = std::make_shared<Plant>(pos);

  _barrier.addPlant(plant);
  game.addPlant(plant);
}

fig::MenuTextures PlantBuilder::getPreviewType() {
  return fig::MenuTextures::Plant;
}
