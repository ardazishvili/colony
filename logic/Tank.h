#ifndef TANK_H
#define TANK_H

#include "../fig/Timer.h"
#include "../view/TankView.h"
#include "AttackUnit.h"

class Game;

enum class HealthLevel { Low, Medium, High };

class Tank : public AttackUnit
{
public:
  enum class Type { Light, Medium, Heavy };

  Tank() = delete;
  Tank(fig::Shader& textureShader,
       fig::Shader& linesShader,
       fig::AStar* router,
       glm::vec3 position,
       Type type = Type::Light,
       HealthLevel healthLevel = HealthLevel::High,
       Shell::Size shellSize = Shell::Size::Small);

private:
  Type _type;
};

std::shared_ptr<Tank> createTank(Game* game,
                                 fig::Shader& textureShader,
                                 fig::Shader& linesShader,
                                 fig::AStar* router,
                                 glm::vec3 position,
                                 Tank::Type type = Tank::Type::Light,
                                 HealthLevel health = HealthLevel::High,
                                 Shell::Size shellSize = Shell::Size::Small);
#endif
