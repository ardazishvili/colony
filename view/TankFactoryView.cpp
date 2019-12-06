#include "TankFactoryView.h"
#include "../globals.h"

float TankFactoryView::TANK_FACTORY_HEALTH_BAR_WIDTH = 1.2f;
float TankFactoryView::TANK_FACTORY_HEALTH_BAR_HEIGHT = 0.15f;

TankFactoryView::TankFactoryView(Shader& shader, glm::vec2 position) :
  _shader(shader), _position(position, 2.37f),
  _healthBar(_shader,
             position.x - 0.3,
             position.y,
             _position.x + TANK_FACTORY_HEALTH_BAR_WIDTH,
             _position.y + TANK_FACTORY_HEALTH_BAR_HEIGHT,
             1)
{
  _texturesType = TexturePackType::PreBuild;
  _model = modelLoader->models()[Models::TankFactory];
  _model->setActiveTexturesPack(TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  /* _healthBar.setTexture("/home/roman/repos/opengl/assets/red.png"); */
}

void TankFactoryView::draw()
{
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::rotate(model, glm::radians(_angle), glm::vec3(0.0f, 0.0f, 1.0f));
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _model->render();
  showHealthBar();
}

bool TankFactoryView::contain(glm::vec2 point) const
{
  const auto radius = 1.41f / 2;
  const auto distance =
    ::sqrt(::pow(_position.x - point.x, 2) + ::pow(_position.y - point.y, 2));

  return distance < radius;
}

glm::vec2 TankFactoryView::position()
{
  return glm::vec2(_position.x, _position.y);
}

void TankFactoryView::setTexture(Status status)
{
  if (status == Status::Selected) {
    _texturesType = TexturePackType::OnSelection;
    _model->setActiveTexturesPack(_texturesType);
  } else if (status == Status::None) {
    _texturesType = TexturePackType::Initial;
    _model->setActiveTexturesPack(_texturesType);
  } else if (status == Status::UnderFire) {
    _texturesType = TexturePackType::UnderFire;
    _model->setActiveTexturesPack(_texturesType);
  } else if (status == Status::Destroyed) {
    _texturesType = TexturePackType::Destroyed;
    _model->setActiveTexturesPack(_texturesType);
  }
}

void TankFactoryView::rotate(float degreeAngle)
{
  _angle = degreeAngle + 180;
}
void TankFactoryView::move(glm::vec2 position)
{
  _position = glm::vec3(position, 2.37f);
  _healthBar.setOffsetXY(position.x, position.y);
}

void TankFactoryView::showHealthBar()
{
  _healthBar.setScaleX(_healthBarScaleFactor);
  _healthBar.render();
}

void TankFactoryView::setHealthBarScaleFactor(float factor)
{
  _healthBarScaleFactor = factor;
}

float TankFactoryView::angle() const
{
  return _angle - 180;
}
