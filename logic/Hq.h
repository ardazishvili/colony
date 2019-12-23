#ifndef HQ_H
#define HQ_H

#include "../engine/Terrain.h"
#include "../view/HqView.h"
#include "BuildableStructure.h"

class Hq : public BuildableStructure
{
public:
  Hq() = delete;
  Hq(Game* game,
     EventManager* eventManager,
     Shader& textureShader,
     Shader& linesShader,
     glm::vec3 position,
     Terrain* terrain);

  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;

private:
  Game* _game;
  EventManager* _eventManager;
  Terrain* _terrain;
  static const int HQ_HP;
};

#endif
