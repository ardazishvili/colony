#include "StructureView.h"
#include "../globals.h"

StructureView::StructureView(Shader& shader,
                             glm::vec3 position,
                             float selectionRadius,
                             HealthBarParams healthBarParams,
                             TexturePackType texturesType) :
  SelectableView(shader,
                 position,
                 selectionRadius,
                 healthBarParams,
                 texturesType)
{
}

void StructureView::showHealthBar()
{
  _healthBar.setScaleX(_healthBarScaleFactor);
  _healthBar.render();
}
