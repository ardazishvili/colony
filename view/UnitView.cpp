#include "view/UnitView.h"

#include "fig/globals.h"

UnitView::UnitView(glm::vec3 position, float selectionRadius,
                   HealthBarParams healthBarParams,
                   fig::TexturePackType texturesType)
    : SelectableView(position, selectionRadius, healthBarParams, texturesType) {
}

void UnitView::showHealthBar() {
  _healthBar.setOffsetXY(_position.x - 0.25, _position.y);
  _healthBar.setScaleX(_healthBarScaleFactor);
  _healthBar.render();
}
