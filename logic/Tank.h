#ifndef TANK_H
#define TANK_H

#include <GL/glew.h> // Initialize with glewInit()

#include <list>

#include "../Timer.h"
#include "../engine/Terrain.h"
#include "../view/TankView.h"
#include "BuildableUnit.h"

class Game;

using Shells = std::list<Shell>;

enum class HealthLevel { Low, Medium, High };

class Tank : public BuildableUnit
{
public:
  enum class Type { Light, Medium, Heavy };

  Tank() = delete;
  Tank(Shader& shader,
       glm::vec3 position,
       Type type = Type::Light,
       HealthLevel healthLevel = HealthLevel::High,
       Shell::Size shellSize = Shell::Size::Small);

  bool isInsideArea(RectangleRegion area);
  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;

  void move();
  void startMoving(glm::vec3 endPoint) override;
  void stopMoving();
  bool isMoving();

  void shootTarget();
  void startShooting(Buildable* other) override;
  void stopShooting();
  bool isShooting();

  void updateShells();
  void setTerrain(Terrain* terrain);

private:
  float getTargetAngle();
  float getTargetDistance();
  float getMouseAngle(int mouseX, int mouseY);
  void reload();
  bool isShellLoaded();

  float _speed;
  glm::vec2 _moveIncrement{ 0, 0 };
  Type _type;
  Shell::Size _shellSize;
  Shells _shells;
  Buildable* _target;
  glm::vec3 _destination;
  Timer _clock;
  std::chrono::milliseconds _shellLoadTime{ 200 };
  Terrain* _terrain;
};

std::shared_ptr<Tank> createTank(Game* game,
                                 Shader& shader,
                                 glm::vec3 position,
                                 Tank::Type type = Tank::Type::Light,
                                 HealthLevel health = HealthLevel::High,
                                 Shell::Size shellSize = Shell::Size::Small);
#endif
