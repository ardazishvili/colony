#include <iostream>

#include <GL/glew.h> // Initialize with glewInit()

#include "../globals.h"
#include "Game.h"
#include "Tank.h"

/* const float Tank::MOVE_STOP_TOL = 0.02; */

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
           AStar* router,
           glm::vec3 position,
           Type type,
           HealthLevel healthLevel,
           Shell::Size sh) :
  BuildableAttackUnit(
    textureShader,
    linesShader,
    std::make_unique<TankView>(textureShader, position, tankSizeMap[type]),
    router,
    sh,
    speedMap[type])
/* _speed(speedMap[type]), _destination(-1, -1) */
{
  _health = healthLevelMap[healthLevel] * tankHitPointsMap[type];
  _maxHealth = _health;
}

/* void Tank::move() */
/* { */
/*   auto prev = _view->position(); */
/*   auto c = _terrain->getXYZ(glm::vec2(prev.x, prev.y) + _moveIncrement); */
/*   _view->move(c); */
/*   bool destinationIsReached = */
/*     ::sqrt(::pow(_view->position().x - _destination.x, 2) + */
/*            ::pow(_view->position().y - _destination.y, 2)) < _speed; */
/*   if (destinationIsReached || isDestroyed()) { */
/*     _movingRoute.pop_back(); */
/*     _path->popLine(); */
/*     if (!_movingRoute.empty()) { */
/*       startMoving(_movingRoute.at(_movingRoute.size() - 1)); */
/*     } else { */
/*       stopMoving(); */
/*     } */
/*   } */
/* } */

/* void Tank::setRoute(glm::vec3 endPoint) */
/* { */
/*   _path = ::makePath(_linesShader, _router, _view->position(), endPoint); */
/*   if (_path != nullptr) { */
/*     _movingRoute = _path->route(); */
/*     startMoving(_movingRoute.at(_movingRoute.size() - 1)); */
/*   } else { */
/*     std::cout << "No path to endpoint!" << std::endl; */
/*   } */
/* } */

/* void Tank::startMoving(glm::vec2 endPoint) */
/* { */
/*   _destination = glm::vec2(endPoint.x, endPoint.y); */

/*   float dy = _destination.y - _view->position().y; */
/*   float dx = _destination.x - _view->position().x; */
/*   float radianAngle = ::atan(dx / dy); */
/*   if (dy < 0) { */
/*     radianAngle += M_PI; */
/*   } */
/*   float degreeAngle = radianAngle * 180.0f / M_PI - 90; */
/*   _view->rotateBody(degreeAngle); */
/*   _moveIncrement.x = _speed * ::sin(radianAngle); */
/*   _moveIncrement.y = _speed * ::cos(radianAngle); */
/* } */

/* void Tank::stopMoving() */
/* { */
/*   _destination = glm::vec3(-1, -1, -1); */
/*   _path.reset(); */
/* } */

/* bool Tank::isMoving() */
/* { */
/*   return _destination != glm::vec2(-1, -1); */
/* } */

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

/* void Tank::setTerrain(Terrain* terrain) */
/* { */
/*   _terrain = terrain; */
/* } */

std::shared_ptr<Tank> createTank(Game* game,
                                 Shader& textureShader,
                                 Shader& linesShader,
                                 AStar* router,
                                 glm::vec3 position,
                                 Tank::Type type,
                                 HealthLevel health,
                                 Shell::Size shellSize)
{
  auto newTank = std::make_shared<Tank>(
    textureShader, linesShader, router, position, type, health, shellSize);
  game->addTank(newTank);
  return newTank;
}
