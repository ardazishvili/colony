#include "view/TankView.h"

#include "ModelLoader.h"
#include "fig/globals.h"
#include "logic/concepts/Buildable.h"

std::map<Status, unsigned int> tankTexturesMap;

TankView::TankView(glm::vec3 position, float tankTypeScaling)
    : AttackUnitView(position, 0.38,
                     {0, 0, TANK_HEALTH_BAR_WIDTH, TANK_HEALTH_BAR_HEIGHT},
                     fig::TexturePackType::Initial),
      _tankTypeScaleFactor(tankTypeScaling) {
  _objScale = tankTypeScaling;
  _model = fig::modelLoader->getModel(fig::ModelType::Tank);
  _hasAnimation = true;
  _healthBar.setOffsetZ(position.z + 0.3);
  _healthBar.setTexture(fig::assets_dir + "/red.png");
}

void TankView::draw() {
  _shader.use();
  updateGun();
  auto percent = _currentGunAngle / 360.0f;
  if (_currentGunAngle == 0) {
    _currentGunAngle += 0.001f;
  }
  if (_currentGunAngle == 360) {
    _currentGunAngle -= 0.001f;
  }
  _model->animate(_shader, fig::Animation::Type::OneShot, percent);

  auto model = glm::mat4(1.0f);
  if (!flatView) {
    model = globeModel();
  } else {
    model = flatModel();
  }
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _model->render();
  showHealthBar();
}

void TankView::move(glm::vec3 newPosition) { _position = newPosition; }

void TankView::rotateBody(float degreeAngle) { _angle = -degreeAngle; }

void TankView::rotateGun(float degreeAngle) {
  _targetGunAngle = degreeAngle - _angle;
  if (_targetGunAngle > 360.0f) {
    _targetGunAngle -= 360.0f;
  }
  auto delta = ::abs(_targetGunAngle) - ::abs(_currentGunAngle);
  if (delta >= 180.f) {
    _currentGunAngle = 359.0f;
  }
}

void TankView::updateGun() {
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
