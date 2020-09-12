#include "PlantBuilder.h"
#include "Game.h"
#include "Plant.h"

PlantBuilder::PlantBuilder(fig::Shader& shader,
                           Game* game,
                           Barrier& barrier,
                           fig::Terrain* terrain) :
  AbstractPlantBuilder(shader, game, barrier, terrain)
{
}

void PlantBuilder::create()
{
  auto randomPos = generateUniformPosition();
  auto pos = _barrier.position();
  pos.x += randomPos.x;
  pos.y += randomPos.y;
  pos.z = _terrain->getXYZ(glm::vec2(pos.x, pos.y)).z +
          fig::Terrain::SUBTERRAIN_OFFSET;
  auto plant = std::make_shared<Plant>(_shader, pos);

  _barrier.addPlant(plant);
  _game->addPlant(plant);
}

fig::MenuTextures PlantBuilder::getPreviewType()
{
  return fig::MenuTextures::Plant;
}
