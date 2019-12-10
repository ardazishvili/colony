#ifndef BARRIER_H
#define BARRIER_H

#include <glm/glm.hpp>

#include "../engine/Terrain.h"
#include "../view/BarrierView.h"
#include "Buildable.h"

class Barrier : public Buildable
{
public:
  Barrier(Shader& textureShader, Shader& colorShader, glm::vec3 position);
  bool isUnderCursor(const glm::vec3& mousePoint) override;
  void render() override;
  void select() override;
  void deselect() override;
  void takeDamage(Shell::Size shellSize) override;
  glm::vec3 position() override;
  UnitBuilders getUnitBuilders(Game& game) override;
  StructureBuilders getStructureBuilders() override;

private:
  void updateHealthBar();

  Shader& _textureShader;
  BarrierView _view;
  std::vector<unsigned int> _vertices;
  float _radius{ 1.0f };
};

#endif
