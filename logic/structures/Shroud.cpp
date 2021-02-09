#include "Shroud.h"
#include "Barrier.h"

#include "../../view/ShroudView.h"

Shroud::Shroud(glm::vec3 position, Barrier& barrier) :
  NonAttackUnit(std::make_unique<ShroudView>(position, barrier.radius())), _barrier(barrier)
{
}

void Shroud::render()
{
  Unit<NonAttackUnit>::render();
  // TODO downcast!
  ShroudView* v = dynamic_cast<ShroudView*>(_view.get());
  if (v->onOrbit()) {
    v->startAnimation();
  }
}

bool Shroud::setUp() const
{
  // TODO downcast!
  ShroudView* v = dynamic_cast<ShroudView*>(_view.get());
  return v->setUp();
}
glm::vec3 Shroud::positionFlat() const
{
  // TODO downcast!
  ShroudView* v = dynamic_cast<ShroudView*>(_view.get());
  return v->positionFlat();
}

glm::vec3 Shroud::positionGlobe() const
{
  // TODO downcast!
  ShroudView* v = dynamic_cast<ShroudView*>(_view.get());
  return v->positionGlobe();
}

Barrier& Shroud::barrier()
{
  return _barrier;
}
