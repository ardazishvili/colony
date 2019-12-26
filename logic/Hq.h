#ifndef HQ_H
#define HQ_H

#include "../engine/Terrain.h"
#include "../view/HqView.h"
#include "BuildableStructure.h"

struct AStar;
class Hq : public BuildableStructure
{
public:
  Hq() = delete;
  Hq(Game* game,
     EventManager* eventManager,
     Shader& textureShader,
     Shader& linesShader,
     AStar* router,
     glm::vec3 position,
     Terrain* terrain);

  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;

private:
  Game* _game;
  EventManager* _eventManager;
  Terrain* _terrain;
  AStar* _router;
  static const int HQ_HP;
};

#endif
