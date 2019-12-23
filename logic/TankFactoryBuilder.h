#ifndef TANK_FACTORY_BUILDER_H
#define TANK_FACTORY_BUILDER_H

#include "../engine/Shader.h"
#include "AbstractStructureBuilder.h"

class TankFactoryBuilder : public AbstractStructureBuilder
{
public:
  TankFactoryBuilder(Game* game,
                     EventManager* eventManager,
                     Shader& textureShader,
                     Shader& linesShader);
  ~TankFactoryBuilder();

  void create() override;
  MenuTextures getPreviewType() override;
};

#endif
