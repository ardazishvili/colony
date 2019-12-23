#ifndef TURBINE_BUILDER_H
#define TURBINE_BUILDER_H

#include "AbstractStructureBuilder.h"

class TurbineBuilder : public AbstractStructureBuilder
{
public:
  TurbineBuilder(Game* game,
                 EventManager* eventManager,
                 Shader& textureShader,
                 Shader& linesShader);

  void create() override;
  MenuTextures getPreviewType() override;
};

#endif
