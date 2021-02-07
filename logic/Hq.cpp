#include "Hq.h"
#include "../figImpl/ColonyEventManager.h"
#include "builders/BarrierBuilder.h"
#include "builders/TankFactoryBuilder.h"
#include "builders/TurbineBuilder.h"

const int Hq::HQ_HP = 500;

Hq::Hq(Game* game,
       ColonyEventManager* eventManager,
       fig::Shader& textureShader,
       fig::Shader& linesShader,
       fig::AStar* router,
       glm::vec3 position,
       fig::Terrain* terrain) :
  GroundStructure(textureShader, linesShader, std::make_unique<HqView>(textureShader, position)),
  _game(game), _eventManager(eventManager), _terrain(terrain), _router(router)
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
    std::make_unique<TankFactoryBuilder>(_game, _eventManager, _textureShader, _linesShader, _router);
  builders.push_back(std::move(tfBuilder));

  std::unique_ptr<AbstractStructureBuilder> bBuilder =
    std::make_unique<BarrierBuilder>(_game, _eventManager, _textureShader, _linesShader, _terrain, _router);
  builders.push_back(std::move(bBuilder));

  std::unique_ptr<AbstractStructureBuilder> tBuilder =
    std::make_unique<TurbineBuilder>(_game, _eventManager, _textureShader, _linesShader);
  builders.push_back(std::move(tBuilder));

  return builders;
}
