#ifndef UNIT_VIEW_H
#define UNIT_VIEW_H

#include "SelectableView.h"

class UnitView : public SelectableView
{
protected:
  UnitView(Shader& shader,
           glm::vec3 position,
           float selectionRadius,
           HealthBarParams healthBarParams,
           TexturePackType texturesType);
  void showHealthBar() override;
};

#endif
