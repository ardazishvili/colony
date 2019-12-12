#include "Hq.h"
#include "BarrierBuilder.h"
#include "TankFactoryBuilder.h"

const int Hq::HQ_HP = 500;

Hq::Hq(Shader& shader, glm::vec3 position, Terrain* terrain) :
  BuildableStructure(shader, std::make_unique<HqView>(shader, position)),
  _terrain(terrain)
{
  _health = HQ_HP;
  _maxHealth = _health;
}

UnitBuilders Hq::getUnitBuilders(Game& game)
{
  return UnitBuilders();
}

StructureBuilders Hq::getStructureBuilders()
{
  StructureBuilders builders = StructureBuilders();
  std::unique_ptr<AbstractStructureBuilder> tfBuilder =
    std::make_unique<TankFactoryBuilder>(_shader);
  builders.push_back(std::move(tfBuilder));

  std::unique_ptr<AbstractStructureBuilder> bBuilder =
    std::make_unique<BarrierBuilder>(_shader, _terrain);
  builders.push_back(std::move(bBuilder));

  return builders;
}

