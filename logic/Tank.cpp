#include <iostream>

#include <GL/glew.h> // Initialize with glewInit()

#include "Game.h"
#include "Tank.h"

std::map<Tank::Type, float> tankSizeMap = {
    {Tank::Type::Light,  0.4f},
    {Tank::Type::Medium, 0.7f},
    {Tank::Type::Heavy,  1.0f},
};

std::map<HealthLevel, float> healthLevelMap = {{HealthLevel::Low, 0.3f},
                                               {HealthLevel::Medium, 0.7f},
                                               {HealthLevel::High, 1.0f}};

std::map<Tank::Type, int> tankHitPointsMap = {{Tank::Type::Light,  30},
                                              {Tank::Type::Medium, 70},
                                              {Tank::Type::Heavy,  100}};

std::map<Tank::Type, float> speedMap = {{Tank::Type::Light, 0.05f},
                                        {Tank::Type::Medium, 0.033f},
                                        {Tank::Type::Heavy, 0.02f}};

Tank::Tank(Shader &shader, glm::vec2 position, Type type,
           HealthLevel healthLevel, Shell::Size sh)
    : _speed(speedMap[type]), 
      _view(shader, position, tankSizeMap[type]),
      _shader(shader),
      _type(type),
      _shellSize(sh),
      _destination(-1, -1) 
{
  _health = healthLevelMap[healthLevel] * tankHitPointsMap[type];
  _maxHealth = _health;
  _target = nullptr;
  reload();
}

void Tank::display() {
  _view.draw();
}

void Tank::move() {
  _view.move(_moveIncrement);
  bool destinationIsReached =
      ::sqrt(::pow(_view.position().x - _destination.x, 2) +
             ::pow(_view.position().y - _destination.y, 2)) < _speed;
  if (destinationIsReached || isDestroyed()) {
    stopMoving();
  }
}

void Tank::startMoving(glm::vec2 endPoint) {
  _destination = endPoint;
  float dy = _destination.y - _view.position().y;
  float dx = _destination.x - _view.position().x;
  float radianAngle = ::atan(dx / dy);
  if (dy < 0) {
    radianAngle += M_PI;
  }
  float degreeAngle = radianAngle * 180.0f / M_PI - 90;
  _view.rotateBody(degreeAngle);
  _moveIncrement.x = _speed * ::sin(radianAngle);
  _moveIncrement.y = _speed * ::cos(radianAngle);
}

void Tank::stopMoving() {
  _destination = glm::vec2(-1, -1);
}

bool Tank::isMoving() { return _destination != glm::vec2(-1, -1); }

void Tank::shootTarget() {
  if (!isShellLoaded()) {
    return;
  }
  if (_target->isDestroyed()) {
    stopShooting();
    return;
  }

  float angle = getTargetAngle() + 90.0f;
  _view.rotateGun(getTargetAngle());
  //TODO magic number = tank length
  Shell shell(_shader, 
	      glm::vec3(_view.position().x, _view.position().y, 0.5f), 
	      glm::radians(angle),
              getTargetDistance(), 
	      _shellSize);
  _shells.push_back(shell);
  _target->takeDamage(_shellSize);
  reload();
}

void Tank::takeDamage(Shell::Size shellSize) {
  if (_status != Status::Destroyed) {
    _status = Status::UnderFire;
    _view.setTexture(Status::UnderFire);
    _health = std::max(0.0f, _health - Shell::SHELL_DAMAGE_MAP.find(shellSize)->second);
    if (_health == 0) {
      _status = Status::Destroyed;
      _view.setTexture(Status::Destroyed);
    }
    updateHealthBar();
  }
}

void Tank::updateHealthBar() {
  auto factor = _health / _maxHealth;
  _view.setHealthBarScaleFactor(factor);
}

void Tank::updateShells() {
  bool pop = false;
  for (auto &shell : _shells) {
    if (shell.isDone()) {
      pop = true;
    }
    shell.update();
  }
  if (pop) {
    _shells.pop_front();
  }
}

glm::vec2 Tank::position() 
{ 
  return _view.position(); 
}

bool Tank::isUnderCursor(const glm::vec2 &point) {
  return _view.contain(point);
}

bool Tank::isInsideArea(glm::vec4 area)
{
  auto c = _view.position();
  return (area.x <= c.x && c.x <= area.z ) && 
	 (area.y <= c.y && c.y <= area.w);
}

bool Tank::isShooting() 
{ 
  return _target != nullptr; 
}

void Tank::select() {
  _status = Status::Selected;
  _view.setTexture(Status::Selected);
}

void Tank::deselect() {
  if (_status != Status::Destroyed) {
    _status = Status::None;
  _view.setTexture(Status::None);
  }
}

void Tank::startShooting(Buildable *other) {
  if (other == this) {
    return;
  }
  _target = other;
}

void Tank::stopShooting() {
  _target = nullptr;
}

void Tank::reload() {
  _clock.reload();
}

bool Tank::isShellLoaded() {
  return _clock.elapsed() >= _shellLoadTime;
}


float Tank::getTargetAngle() {
  float targetX = _target->position().x;
  float targetY = _target->position().y;
  float thisX = this->position().x;
  float thisY = this->position().y;
  float radianAngle = ::atan((targetY - thisY) / (targetX - thisX));
  float degreeAngle = radianAngle * 180.0f / M_PI;
  if (targetX - thisX < 0) {
    degreeAngle += 180.0f;
  }

  return degreeAngle;
}

float Tank::getTargetDistance() {
  float targetX = _target->position().x;
  float targetY = _target->position().y;
  float thisX = this->position().x;
  float thisY = this->position().y;
  return ::sqrt(::pow(targetX - thisX, 2) + ::pow(targetY - thisY, 2));
}

float Tank::getMouseAngle(int mouseX, int mouseY) {
  float thisX = this->position().x;
  float thisY = this->position().y;
  float radianAngle = ::atan((mouseY - thisY) / (mouseX - thisX));
  float degreeAngle = radianAngle * 180.0f / M_PI;
  if (mouseX - thisX < 0) {
    degreeAngle += 180.0f;
  }

  return degreeAngle;
}

UnitBuilders Tank::getUnitBuilders(Game &game) {
  // TODO
  return UnitBuilders();
}

StructureBuilders Tank::getStructureBuilders() {
  // TODO
  return StructureBuilders();
}

std::shared_ptr<Tank> createTank(Game &game, Shader &shader, glm::vec2 position,
                                 Tank::Type type,
				 HealthLevel health,
				 Shell::Size shellSize) {
  auto newTank = std::make_shared<Tank>(shader, position, type, health, shellSize);
  game.addTank(newTank);
  return newTank;
}
