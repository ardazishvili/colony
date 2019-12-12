#ifndef HQ_H
#define HQ_H

#include "../engine/Terrain.h"
#include "../view/HqView.h"
#include "BuildableStructure.h"

class Hq : public BuildableStructure
{
public:
  Hq() = delete;
  Hq(Shader& shader, glm::vec3 position, Terrain* terrain);

  void render() override;
  /* void select() override; */
  /* void deselect() override; */
  void takeDamage(Shell::Size shellSize) override;
  glm::vec3 position() override;
  UnitBuilders getUnitBuilders(Game& game) override;
  StructureBuilders getStructureBuilders() override;
  void setAngle(float angle) override;
  void setPosition(glm::vec3 position) override;
  void commit() override;

private:
  Terrain* _terrain;
  void updateHealthBar() override;
  static const int HQ_HP;
};

#endif
