#ifndef HQ_H
#define HQ_H

#include "BuildableStructure.h"
#include "../view/HqView.h"

class Hq : public BuildableStructure {
public:
  Hq() = delete;
  Hq(Shader& shader, glm::vec2 position);

  bool isUnderCursor(const glm::vec2& mousePoint) override;
  void display() override;
  void select() override;
  void deselect() override;
  void takeDamage(Shell::Size shellSize) override;
  glm::vec2 position() override;
  UnitBuilders getUnitBuilders(Game& game) override;
  StructureBuilders getStructureBuilders() override;
  void setAngle(float angle) override;
  void setPosition(glm::vec2 position) override;
  void commit() override;

private:
  Shader& _shader;
  void updateHealthBar() override;
  HqView _view;
  static const int HQ_HP;
};

#endif
