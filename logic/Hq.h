#ifndef HQ_H
#define HQ_H

#include "../fig//math/AStar.h"
#include "../fig/Terrain.h"
#include "../view/HqView.h"
#include "GroundStructure.h"

struct AStar;
class Hq : public GroundStructure
{
public:
  Hq() = delete;
  Hq(Game* game,
     ColonyEventManager* eventManager,
     fig::Shader& textureShader,
     fig::Shader& linesShader,
     fig::AStar* router,
     glm::vec3 position,
     fig::Terrain* terrain);

  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;

private:
  Game* _game;
  ColonyEventManager* _eventManager;
  fig::Terrain* _terrain;
  fig::AStar* _router;
  static const int HQ_HP;
};

#endif
