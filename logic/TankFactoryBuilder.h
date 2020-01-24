#ifndef TANK_FACTORY_BUILDER_H
#define TANK_FACTORY_BUILDER_H

#include "../fig/Shader.h"
#include "AbstractStructureBuilder.h"

struct AStar;
class TankFactoryBuilder : public AbstractStructureBuilder
{
public:
  TankFactoryBuilder(Game* game,
                     EventManager* eventManager,
                     Shader& textureShader,
                     Shader& linesShader,
                     AStar* router);
  ~TankFactoryBuilder();

  void create() override;
  MenuTextures getPreviewType() override;

private:
  AStar* _router;
};

#endif
