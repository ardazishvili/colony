#ifndef BARRIER_H
#define BARRIER_H

#include <glm/glm.hpp>

#include "../engine/Terrain.h"
#include "../view/BarrierView.h"
#include "AbstractPlant.h"
#include "EnergyStructure.h"

class Barrier : public EnergyStructure
{
public:
  Barrier(Shader& textureShader,
          Shader& linesShader,
          glm::vec3 position,
          Terrain* terrain);
  void render() override;
  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;
  void addPlant(std::shared_ptr<AbstractPlant> p);
  void commit() override;
  glm::vec3 shroudPosition() const;

private:
  float _radius{ 1.0f };
  Terrain* _terrain;
  std::shared_ptr<LivingArea> _livingArea{ nullptr };
  Plants _plants;
  Timer _clock;
  std::chrono::milliseconds _bioUpdateTime{ 1000 };
  static const int BARRIER_HP;
};

#endif
