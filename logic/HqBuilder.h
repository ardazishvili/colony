#ifndef HQ_BUILDER_H
#define HQ_BUILDER_H

#include "../engine/Shader.h"
#include "AbstractStructureBuilder.h"

class HqBuilder : public AbstractStructureBuilder
{
public:
  HqBuilder(Shader& shader);
  ~HqBuilder();

  void create() override;
  MenuTextures getPreviewType() override;

private:
  Shader& _shader;
};

#endif
