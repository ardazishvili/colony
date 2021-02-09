#ifndef HQ_H
#define HQ_H

#include "../../fig/Terrain.h"
#include "../../view/HqView.h"
#include "GroundStructure.h"

class Hq : public GroundStructure
{
public:
  Hq() = delete;
  Hq(Game* game, ColonyEventManager* eventManager, glm::vec3 position, fig::Terrain* terrain);

  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;

private:
  Game* _game;
  ColonyEventManager* _eventManager;
  fig::Terrain* _terrain;
  static const int HQ_HP;
};

#endif
