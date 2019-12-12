#ifndef BARRIER_H
#define BARRIER_H

#include <glm/glm.hpp>

#include "../engine/Terrain.h"
#include "../view/BarrierView.h"
#include "BuildableStructure.h"
#include "Plant.h"

class Barrier : public BuildableStructure
{
public:
  Barrier(Shader& shader, glm::vec3 position, Terrain* terrain);
  /* bool isUnderCursor(const glm::vec3& mousePoint) override; */
  void render() override;
  void select() override;
  void deselect() override;
  void takeDamage(Shell::Size shellSize) override;
  glm::vec3 position() override;
  UnitBuilders getUnitBuilders(Game& game) override;
  StructureBuilders getStructureBuilders() override;
  void addPlant(std::shared_ptr<Plant> p);
  void setAngle(float angle) override;
  void setPosition(glm::vec3 position) override;
  void commit() override;

private:
  void updateHealthBar() override;

  /* Shader& _textureShader; */
  /* BarrierView _view; */
  std::vector<unsigned int> _vertices;
  float _radius{ 1.0f };
  Terrain* _terrain;
  std::shared_ptr<LivingArea> _livingArea{ nullptr };
  Plants _plants;

  Timer _clock;
  std::chrono::milliseconds _bioUpdateTime{ 1000 };
  static const int BARRIER_HP;
};

#endif
