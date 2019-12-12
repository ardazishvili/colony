#include "SelectableView.h"

SelectableView::SelectableView(Shader& shader,
                               glm::vec3 position,
                               float selectionRadius) :
  View(shader, position),
  _selectionRadius(selectionRadius)
{
}

bool SelectableView::contain(glm::vec3 point) const
{
  const auto distance =
    ::sqrt(::pow(_position.x - point.x, 2) + ::pow(_position.y - point.y, 2));

  return distance < _selectionRadius;
}
