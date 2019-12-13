#include "UnitView.h"
#include "../globals.h"

UnitView::UnitView(Shader& shader,
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

void UnitView::showHealthBar()
{
  _healthBar.setOffsetXY(_position.x - 0.25, _position.y);
  _healthBar.setScaleX(_healthBarScaleFactor);
  _healthBar.setPitchAngle();
  _healthBar.render();
}
