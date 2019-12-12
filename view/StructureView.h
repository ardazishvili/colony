#ifndef STRUCTURE_VIEW_H
#define STRUCTURE_VIEW_H

#include "SelectableView.h"

class StructureView : public SelectableView
{
protected:
  StructureView(Shader& shader,
                glm::vec3 position,
                float selectionRadius,
                HealthBarParams healthBarParams,
                TexturePackType texturesType);
  void showHealthBar() override;
};

#endif
