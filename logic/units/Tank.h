#pragma once

#include <glm/detail/type_vec.hpp>

#include "fig/Timer.h"
#include "logic/units/AttackUnit.h"
#include "view/TankView.h"

class Game;

enum class HealthLevel { Low, Medium, High };

class Tank : public AttackUnit {
 public:
  enum class Type { Light, Medium, Heavy };

  Tank() = delete;
  Tank(const Tank& other) = default;
  Tank(Tank&& other) = default;
  Tank& operator=(const Tank&) = default;
  Tank& operator=(Tank&&) = default;
  ~Tank() = default;

  Tank(fig::AStar& router, glm::vec3 position, Type type = Type::Light,
       HealthLevel healthLevel = HealthLevel::High,
       Shell::Size shellSize = Shell::Size::Small);

 private:
  Type _type;
};

void createTank(Game& game, fig::AStar& router, glm::vec3 position,
                Tank::Type type = Tank::Type::Light,
                HealthLevel health = HealthLevel::High,
                Shell::Size shellSize = Shell::Size::Small);

void createTank(Game& game, fig::AStar& router, glm::vec3 position,
                glm::vec3 destination, Tank::Type type = Tank::Type::Light,
                HealthLevel health = HealthLevel::High,
                Shell::Size shellSize = Shell::Size::Small);
