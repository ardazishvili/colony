#ifndef SHROUD_H
#define SHROUD_H

#include "NonAttackUnit.h"

class Barrier;
class Shroud : public NonAttackUnit
{
public:
  Shroud() = delete;
  Shroud(Shader& textureShader,
         Shader& linesShader,
         AStar* router,
         glm::vec3 position,
         Barrier& barrier);
  void render() override;
  bool setUp() const;
  glm::vec3 positionFlat() const;
  glm::vec3 positionGlobe() const;

  UnitBuilders getUnitBuilders(Game* game) override
  {
    return UnitBuilders();
  };
  StructureBuilders getStructureBuilders() override
  {
    return StructureBuilders();
  };
  Barrier& barrier();

private:
  Barrier& _barrier;
};

#endif
