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
            Shader& shader,
            Terrain* terrain);
  ~HqBuilder();

  void create() override;
  MenuTextures getPreviewType() override;

private:
  Shader& _shader;
  Terrain* _terrain;
};

#endif
