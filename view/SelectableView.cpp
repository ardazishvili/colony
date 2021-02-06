#include "SelectableView.h"

SelectableView::SelectableView(fig::Shader& shader,
                               glm::vec3 position,
                               float selectionRadius,
                               HealthBarParams hbp,
                               fig::TexturePackType texturesType) :
  View(shader, position),
  _selectionRadius(selectionRadius), _healthBar(shader.camera(),
                                                shader,
                                                position.x + hbp.xOffset,
                                                position.y + hbp.yOffset,
                                                position.x + hbp.width,
                                                position.y + hbp.height,
                                                1),
  _texturesType(texturesType)
{
}

bool SelectableView::contain(glm::vec3 point) const
{
  const auto distance = ::sqrt(::pow(_position.x - point.x, 2) + ::pow(_position.y - point.y, 2));

  return distance < _selectionRadius;
}

void SelectableView::setHealthBarScaleFactor(float factor)
{
  _healthBarScaleFactor = factor;
}

void SelectableView::setTexture(Status status)
{
  if (status == Status::Selected) {
    _texturesType = fig::TexturePackType::OnSelection;
    _model->setActiveTexturesPack(_texturesType);
  } else if (status == Status::None) {
    _texturesType = fig::TexturePackType::Initial;
    _model->setActiveTexturesPack(_texturesType);
  } else if (status == Status::UnderFire) {
    _texturesType = fig::TexturePackType::UnderFire;
    _model->setActiveTexturesPack(_texturesType);
  } else if (status == Status::Destroyed) {
    _texturesType = fig::TexturePackType::Destroyed;
    _model->setActiveTexturesPack(_texturesType);
  }
}

float SelectableView::angle() const
{
  return _angle - 180;
}
