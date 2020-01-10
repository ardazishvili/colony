#ifndef TANK_H
#define TANK_H

#include <GL/glew.h> // Initialize with glewInit()

#include <list>

#include "../Timer.h"
#include "../engine/LinesObject.h"
#include "../engine/Terrain.h"
#include "../view/TankView.h"
#include "AttackUnit.h"

class Game;

using Shells = std::list<Shell>;

enum class HealthLevel { Low, Medium, High };

class Tank : public AttackUnit
{
public:
  enum class Type { Light, Medium, Heavy };

  Tank() = delete;
  Tank(Shader& textureShader,
       Shader& linesShader,
       AStar* router,
       glm::vec3 position,
       Type type = Type::Light,
       HealthLevel healthLevel = HealthLevel::High,
       Shell::Size shellSize = Shell::Size::Small);

private:
  Type _type;
};

std::shared_ptr<Tank> createTank(Game* game,
                                 Shader& textureShader,
                                 Shader& linesShader,
                                 AStar* router,
                                 glm::vec3 position,
                                 Tank::Type type = Tank::Type::Light,
                                 HealthLevel health = HealthLevel::High,
                                 Shell::Size shellSize = Shell::Size::Small);
#endif
