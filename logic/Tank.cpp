#include <iostream>

#include <GL/glew.h> // Initialize with glewInit()

#include "Game.h"
#include "Tank.h"

std::map<Tank::Type, float> tankSizeMap = {
  { Tank::Type::Light, 0.4f },
  { Tank::Type::Medium, 0.7f },
  { Tank::Type::Heavy, 1.0f },
};

std::map<HealthLevel, float> healthLevelMap = { { HealthLevel::Low, 0.3f },
                                                { HealthLevel::Medium, 0.7f },
                                                { HealthLevel::High, 1.0f } };

std::map<Tank::Type, int> tankHitPointsMap = { { Tank::Type::Light, 30 },
                                               { Tank::Type::Medium, 70 },
                                               { Tank::Type::Heavy, 100 } };

std::map<Tank::Type, float> speedMap = { { Tank::Type::Light, 0.05f },
                                         { Tank::Type::Medium, 0.033f },
                                         { Tank::Type::Heavy, 0.02f } };

Tank::Tank(Shader& textureShader,
           Shader& linesShader,
           glm::vec3 position,
           Type type,
           HealthLevel healthLevel,
           Shell::Size sh) :
  BuildableUnit(
    textureShader,
    linesShader,
    std::make_unique<TankView>(textureShader, position, tankSizeMap[type])),
  _speed(speedMap[type]), _shellSize(sh), _destination(-1, -1, -1)
{
  _health = healthLevelMap[healthLevel] * tankHitPointsMap[type];
  _maxHealth = _health;
  _target = nullptr;
  reload();
}

void Tank::move()
{
  auto prev = _view->position();
  _path.setStart(prev);
  auto c = _terrain->getXYZ(glm::vec2(prev.x, prev.y) + _moveIncrement);
  _view->move(c);
  bool destinationIsReached =
    ::sqrt(::pow(_view->position().x - _destination.x, 2) +
           ::pow(_view->position().y - _destination.y, 2)) < _speed;
  if (destinationIsReached || isDestroyed()) {
    stopMoving();
  }
}

void Tank::startMoving(glm::vec3 endPoint)
{
  _destination = endPoint;
  float dy = _destination.y - _view->position().y;
  float dx = _destination.x - _view->position().x;
  float radianAngle = ::atan(dx / dy);
  if (dy < 0) {
    radianAngle += M_PI;
  }
  float degreeAngle = radianAngle * 180.0f / M_PI - 90;
  _view->rotateBody(degreeAngle);
  _moveIncrement.x = _speed * ::sin(radianAngle);
  _moveIncrement.y = _speed * ::cos(radianAngle);

  _path.setUp(_view->position(), endPoint);
}

void Tank::stopMoving()
{
  _destination = glm::vec3(-1, -1, -1);
  _path.clear();
}

bool Tank::isMoving()
{
  return _destination != glm::vec3(-1, -1, -1);
}

void Tank::shootTarget()
{
  if (!isShellLoaded()) {
    return;
  }
  if (_target->isDestroyed()) {
    stopShooting();
    return;
  }

  float angle = getTargetAngle() + 90.0f;
  _view->rotateGun(getTargetAngle());
  // TODO magic number = tank length
  Shell shell(_textureShader,
              glm::vec3(_view->position().x, _view->position().y, 0.5f),
              glm::radians(angle),
              getTargetDistance(),
              _shellSize);
  _shells.push_back(shell);
  _target->takeDamage(_shellSize);
  reload();
}

void Tank::updateShells()
{
  bool pop = false;
  for (auto& shell : _shells) {
    if (shell.isDone()) {
      pop = true;
    }
    shell.update();
  }
  if (pop) {
    _shells.pop_front();
  }
}

bool Tank::isInsideArea(Points area)
{
  auto tmp = _view->position();
  auto m = glm::vec2(tmp.x, tmp.y);
  auto a = glm::vec2(area.at(0).x, area.at(0).y);
  auto b = glm::vec2(area.at(1).x, area.at(1).y);
  auto d = glm::vec2(area.at(3).x, area.at(3).y);
  glm::vec2 am = m - a;
  glm::vec2 ab = b - a;
  glm::vec2 ad = d - a;
  const bool cond1 =
    (0.0f < glm::dot(am, ab)) && (glm::dot(am, ab) < glm::dot(ab, ab));
  const bool cond2 =
    (0.0f < glm::dot(am, ad)) && (glm::dot(am, ad) < glm::dot(ad, ad));
  return cond1 && cond2;
}

bool Tank::isShooting()
{
  return _target != nullptr;
}

void Tank::startShooting(Buildable* other)
{
  if (other == this) {
    return;
  }
  _target = other;
}

void Tank::stopShooting()
{
  _target = nullptr;
}

void Tank::reload()
{
  _clock.reload();
}

bool Tank::isShellLoaded()
{
  return _clock.elapsed() >= _shellLoadTime;
}

float Tank::getTargetAngle()
{
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

float Tank::getTargetDistance()
{
  float targetX = _target->position().x;
  float targetY = _target->position().y;
  float thisX = this->position().x;
  float thisY = this->position().y;
  return ::sqrt(::pow(targetX - thisX, 2) + ::pow(targetY - thisY, 2));
}

float Tank::getMouseAngle(int mouseX, int mouseY)
{
  float thisX = this->position().x;
  float thisY = this->position().y;
  float radianAngle = ::atan((mouseY - thisY) / (mouseX - thisX));
  float degreeAngle = radianAngle * 180.0f / M_PI;
  if (mouseX - thisX < 0) {
    degreeAngle += 180.0f;
  }

  return degreeAngle;
}

UnitBuilders Tank::getUnitBuilders(Game* game)
{
  // TODO
  return UnitBuilders();
}

StructureBuilders Tank::getStructureBuilders()
{
  // TODO
  return StructureBuilders();
}

void Tank::setTerrain(Terrain* terrain)
{
  _terrain = terrain;
}

std::shared_ptr<Tank> createTank(Game* game,
                                 Shader& textureShader,
                                 Shader& linesShader,
                                 glm::vec3 position,
                                 Tank::Type type,
                                 HealthLevel health,
                                 Shell::Size shellSize)
{
  auto newTank = std::make_shared<Tank>(
    textureShader, linesShader, position, type, health, shellSize);
  game->addTank(newTank);
  return newTank;
}
