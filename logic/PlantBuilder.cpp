#include "PlantBuilder.h"
#include "Game.h"
#include "Plant.h"

PlantBuilder::PlantBuilder(Shader& shader,
                           Game* game,
                           Barrier& barrier,
                           Terrain* terrain) :
  AbstractPlantBuilder(shader, game, barrier, terrain)
{
}

void PlantBuilder::create()
{
  auto randomPos = generateUniformPosition();
  auto pos = _barrier.position();
  pos.x += randomPos.x;
  pos.y += randomPos.y;
  pos.z =
    _terrain->getXYZ(glm::vec2(pos.x, pos.y)).z + Terrain::SUBTERRAIN_OFFSET;
  auto plant = std::make_shared<Plant>(_shader, pos);

  _barrier.addPlant(plant);
  _game->addPlant(plant);
}

MenuTextures PlantBuilder::getPreviewType()
{
  return MenuTextures::Plant;
}
