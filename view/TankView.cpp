#include "../imgui/imgui.h"

#include "../globals.h"
#include "../logic/Buildable.h"
#include "../logic/EventManager.h"
#include "TankView.h"

float TankView::TANK_GUN_ANGLE_INCREMENT = 1.5;
float TankView::TANK_GUN_ANGLE_TOLERANCE = 1.5;
float TankView::TANK_HEALTH_BAR_WIDTH = 0.5;
float TankView::TANK_HEALTH_BAR_HEIGHT = 0.04;
std::map<Status, unsigned int> tankTexturesMap;

TankView::TankView(Shader& shader, glm::vec3 position, float tankTypeScaling) :
  SelectableView(shader,
                 position,
                 0.38,
                 { 0, 0, TANK_HEALTH_BAR_WIDTH, TANK_HEALTH_BAR_HEIGHT }),
  _tankSizeScaleFactor(tankTypeScaling)
{
  _model = modelLoader->models()[Models::Tank];
  _texturesType = TexturePackType::Initial;
  _hasAnimation = true;
  _healthBar.setOffsetZ(position.z + 0.3);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");
}

void TankView::draw()
{
  _shader.use();
  updateGun();
  auto percent = _currentGunAngle / 360.0f;
  if (_currentGunAngle == 0) {
    _currentGunAngle += 0.001f;
  }
  if (_currentGunAngle == 360) {
    _currentGunAngle -= 0.001f;
  }
  _model->animate(_shader, Animation::Type::OneShot, percent);

  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model =
    glm::rotate(model, glm::radians(_bodyAngle), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(_tankSizeScaleFactor));
  model = glm::scale(model, glm::vec3(VIEW_SCALE));
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _model->render();
  showHealthBar();
}

void TankView::move(glm::vec3 newPosition)
{
  _position = newPosition;
}

void TankView::rotateBody(float degreeAngle)
{
  _bodyAngle = -degreeAngle;
}

void TankView::rotateGun(float degreeAngle)
{
  _targetGunAngle = degreeAngle - _bodyAngle;
  if (_targetGunAngle > 360.0f) {
    _targetGunAngle -= 360.0f;
  }
  auto delta = ::abs(_targetGunAngle) - ::abs(_currentGunAngle);
  if (delta >= 180.f) {
    _currentGunAngle = 359.0f;
  }
}

void TankView::setTexture(Status status)
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

void TankView::updateGun()
{
  auto delta = _targetGunAngle - _currentGunAngle;
  if (delta < -180.0f) {
    if (_currentGunAngle > 180.0f) {
      _targetGunAngle += 360.0f;
    } else {
      _targetGunAngle += 180.0f;
    }
  }
  if (::abs(delta) > TANK_GUN_ANGLE_TOLERANCE) {
    if (delta > 0.f) {
      _currentGunAngle += TANK_GUN_ANGLE_INCREMENT;
      if (_currentGunAngle > 360) {
        _currentGunAngle = TANK_GUN_ANGLE_INCREMENT;
      }
    } else {
      _currentGunAngle -= TANK_GUN_ANGLE_INCREMENT;
      if (_currentGunAngle < -359) {
        _currentGunAngle = TANK_GUN_ANGLE_INCREMENT;
      }
    }
  }
}

void TankView::showHealthBar()
{
  _healthBar.setOffsetXY(_position.x - 0.25, _position.y);
  _healthBar.setScaleX(_healthBarScaleFactor);
  _healthBar.setPitchAngle(-camera.getPitch());
  _healthBar.render();
}

