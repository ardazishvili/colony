#ifndef HQ_BUILDER_H
#define HQ_BUILDER_H

#include "../engine/Shader.h"
#include "../engine/Terrain.h"
#include "AbstractStructureBuilder.h"

class HqBuilder : public AbstractStructureBuilder
{
public:
  HqBuilder(Game* game,
            EventManager* eventManager,
            Shader& textureShader,
            Shader& linesShader,
            Terrain* terrain);
  ~HqBuilder();

  void create() override;
  MenuTextures getPreviewType() override;

private:
  Terrain* _terrain;
};

#endif
