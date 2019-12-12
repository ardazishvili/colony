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

float StructureView::angle() const
{
  return _angle - 180;
}

void StructureView::rotate(float degreeAngle)
{
  _angle = degreeAngle + 180;
}

void StructureView::move(glm::vec3 position)
{
  _position = glm::vec3(position);
  _healthBar.setOffsetXY(position.x, position.y);
}
