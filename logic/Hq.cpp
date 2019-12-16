#include "Hq.h"
#include "BarrierBuilder.h"
#include "EventManager.h"
#include "TankFactoryBuilder.h"
#include "TurbineBuilder.h"

const int Hq::HQ_HP = 500;

Hq::Hq(Game* game,
       EventManager* eventManager,
       Shader& shader,
       glm::vec3 position,
       Terrain* terrain) :
  BuildableStructure(shader, std::make_unique<HqView>(shader, position)),
  _game(game), _eventManager(eventManager), _terrain(terrain)
{
  _health = HQ_HP;
  _maxHealth = _health;
}

UnitBuilders Hq::getUnitBuilders(Game* game)
{
  return UnitBuilders();
}

StructureBuilders Hq::getStructureBuilders()
{
  StructureBuilders builders = StructureBuilders();
  std::unique_ptr<AbstractStructureBuilder> tfBuilder =
    std::make_unique<TankFactoryBuilder>(_game, _eventManager, _shader);
  builders.push_back(std::move(tfBuilder));

  std::unique_ptr<AbstractStructureBuilder> bBuilder =
    std::make_unique<BarrierBuilder>(
      _game, _eventManager, _shader, _eventManager->getLinesShader(), _terrain);
  builders.push_back(std::move(bBuilder));

  std::unique_ptr<AbstractStructureBuilder> tBuilder =
    std::make_unique<TurbineBuilder>(
      _game, _eventManager, _shader, _eventManager->getLinesShader());
  builders.push_back(std::move(tBuilder));

  return builders;
}

