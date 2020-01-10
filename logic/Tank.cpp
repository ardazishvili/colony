#include <iostream>

#include <GL/glew.h> // Initialize with glewInit()

#include "../globals.h"
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
{
  _health = healthLevelMap[healthLevel] * tankHitPointsMap[type];
  _maxHealth = _health;
}

/* bool Tank::isInsideArea(Points area) */
/* { */
/*   auto tmp = _view->position(); */
/*   auto m = glm::vec2(tmp.x, tmp.y); */
/*   auto a = glm::vec2(area.at(0).x, area.at(0).y); */
/*   auto b = glm::vec2(area.at(1).x, area.at(1).y); */
/*   auto d = glm::vec2(area.at(3).x, area.at(3).y); */
/*   glm::vec2 am = m - a; */
/*   glm::vec2 ab = b - a; */
/*   glm::vec2 ad = d - a; */
/*   const bool cond1 = */
/*     (0.0f < glm::dot(am, ab)) && (glm::dot(am, ab) < glm::dot(ab, ab)); */
/*   const bool cond2 = */
/*     (0.0f < glm::dot(am, ad)) && (glm::dot(am, ad) < glm::dot(ad, ad)); */
/*   return cond1 && cond2; */
/* } */

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
