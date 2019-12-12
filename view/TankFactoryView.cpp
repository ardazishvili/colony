#include "TankFactoryView.h"
#include "../globals.h"

float TankFactoryView::TANK_FACTORY_HEALTH_BAR_WIDTH = 1.2f;
float TankFactoryView::TANK_FACTORY_HEALTH_BAR_HEIGHT = 0.15f;

TankFactoryView::TankFactoryView(Shader& shader, glm::vec3 position) :
  SelectableView(
    shader,
    position,
    1.41 / 2,
    { -0.3, 0, TANK_FACTORY_HEALTH_BAR_WIDTH, TANK_FACTORY_HEALTH_BAR_HEIGHT })
{
  _texturesType = TexturePackType::PreBuild;
  _model = modelLoader->models()[Models::TankFactory];
  _model->setActiveTexturesPack(TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");
}

void TankFactoryView::draw()
{
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::rotate(model, glm::radians(_angle), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(VIEW_SCALE));
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _model->render();
  showHealthBar();
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
void TankFactoryView::move(glm::vec3 position)
{
  _position = glm::vec3(position);
  _healthBar.setOffsetXY(position.x, position.y);
}

void TankFactoryView::showHealthBar()
{
  _healthBar.setScaleX(_healthBarScaleFactor);
  _healthBar.render();
}

float TankFactoryView::angle() const
{
  return _angle - 180;
}
