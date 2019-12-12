#include "SelectableView.h"

SelectableView::SelectableView(Shader& shader,
                               glm::vec3 position,
                               float selectionRadius,
                               HealthBarParams hbp) :
  View(shader, position),
  _selectionRadius(selectionRadius), _healthBar(shader,
                                                position.x + hbp.xOffset,
                                                position.y + hbp.yOffset,
                                                position.x + hbp.width,
                                                position.y + hbp.height,
                                                1)
{
}

bool SelectableView::contain(glm::vec3 point) const
{
  const auto distance =
    ::sqrt(::pow(_position.x - point.x, 2) + ::pow(_position.y - point.y, 2));

  return distance < _selectionRadius;
}

void SelectableView::setHealthBarScaleFactor(float factor)
{
  _healthBarScaleFactor = factor;
}
