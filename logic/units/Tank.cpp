#include "logic/units/Tank.h"

#include <glm/detail/type_vec.hpp>
#include <memory>

#include "fig/globals.h"
#include "logic/Game.h"

std::map<Tank::Type, float> tankSizeMap = {
    {Tank::Type::Light, 0.4f},
    {Tank::Type::Medium, 0.7f},
    {Tank::Type::Heavy, 1.0f},
};

std::map<HealthLevel, float> healthLevelMap = {{HealthLevel::Low, 0.3f},
                                               {HealthLevel::Medium, 0.7f},
                                               {HealthLevel::High, 1.0f}};

std::map<Tank::Type, int> tankHitPointsMap = {{Tank::Type::Light, 30},
                                              {Tank::Type::Medium, 70},
                                              {Tank::Type::Heavy, 100}};

std::map<Tank::Type, float> speedMap = {{Tank::Type::Light, 0.05f},
                                        {Tank::Type::Medium, 0.033f},
                                        {Tank::Type::Heavy, 0.02f}};

Tank::Tank(fig::AStar& router, glm::vec3 position, Type type,
           HealthLevel healthLevel, Shell::Size sh)
    : AttackUnit(std::make_unique<TankView>(position, tankSizeMap[type]),
                 router, sh, speedMap[type]) {
  _health = healthLevelMap[healthLevel] * tankHitPointsMap[type];
  _maxHealth = _health;
}

void createTank(Game& game, fig::AStar& router, glm::vec3 position,
                Tank::Type type, HealthLevel health, Shell::Size shellSize) {
  game.addTank(
      std::make_unique<Tank>(router, position, type, health, shellSize));
}

void createTank(Game& game, fig::AStar& router, glm::vec3 position,
                glm::vec3 destination, Tank::Type type, HealthLevel health,
                Shell::Size shellSize) {
  game.addTankAndDestination(
      std::make_unique<Tank>(router, position, type, health, shellSize),
      destination);
}
