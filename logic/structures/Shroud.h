#ifndef SHROUD_H
#define SHROUD_H

#include "../units/NonAttackUnit.h"

class Barrier;
class Shroud : public NonAttackUnit
{
public:
  Shroud() = delete;
  Shroud(fig::AStar* router, glm::vec3 position, Barrier& barrier);
  void render() override;
  bool setUp() const;
  glm::vec3 positionFlat() const;
  glm::vec3 positionGlobe() const;
  Barrier& barrier();

private:
  Barrier& _barrier;
};

#endif
