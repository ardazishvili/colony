#ifndef TANK_FACTORY_H
#define TANK_FACTORY_H

#include <GL/glew.h>

#include "../view/TankFactoryView.h"
#include "BuildableStructure.h"
#include "Tank.h"

class Game;

class TankFactory : public BuildableStructure
{
public:
  TankFactory() = delete;
  TankFactory(Shader& shader, glm::vec3 position);

  void createTank(Game& game,
                  Tank::Type tankType,
                  HealthLevel healthLevel,
                  Shell::Size shellSize);
  void render() override;
  bool isUnderCursor(const glm::vec3& mousePoint) override;
  void select() override;
  void deselect() override;
  void takeDamage(Shell::Size shellSize) override;
  glm::vec3 position() override;
  UnitBuilders getUnitBuilders(Game& game) override;
  StructureBuilders getStructureBuilders() override;
  void setAngle(float angle) override;
  void setPosition(glm::vec3 position) override;
  void commit() override;

private:
  void updateHealthBar() override;
  void addUnitBuilder(Game& game,
                      UnitBuilders& builders,
                      Tank::Type type,
                      HealthLevel healthLevel,
                      Shell::Size shellSize);

  TankFactoryView _view;
  Shader& _shader;
  static const int TANK_FACTORY_HP;
};

#endif
