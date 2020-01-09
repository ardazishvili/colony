#ifndef SHROUD_H
#define SHROUD_H

#include "BuildableUnit.h"

class Barrier;
class Shroud : public BuildableUnit
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

  // FIXME stubs for now
  void startShooting(Buildable* other) override{};
  void startMoving(glm::vec2 endPoint) override{};
  void setRoute(glm::vec3 endPoint) override{};
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
