#include "StructureView.h"
#include "../fig/globals.h"

StructureView::StructureView(fig::Shader& shader,
                             glm::vec3 position,
                             float selectionRadius,
                             HealthBarParams healthBarParams,
                             fig::TexturePackType texturesType) :
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

void StructureView::rotate(float degreeAngle)
{
  _angle = degreeAngle + 180;
}

void StructureView::move(glm::vec3 position)
{
  _position = glm::vec3(position);
  _healthBar.setOffsetXY(position.x, position.y);
}
