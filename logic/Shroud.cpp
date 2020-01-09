#include "Shroud.h"
#include "../view/ShroudView.h"

Shroud::Shroud(Shader& textureShader,
               Shader& linesShader,
               AStar* router,
               glm::vec3 position) :
  BuildableUnit(
    textureShader,
    linesShader,
    std::make_unique<ShroudView>(textureShader, linesShader, position),
    router)
{
}

void Shroud::render()
{
  BuildableUnit::render();
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
  return v->shroudSetUp();
}
glm::vec3 Shroud::shroudPositionFlat() const
{
  // TODO downcast!
  ShroudView* v = dynamic_cast<ShroudView*>(_view.get());
  return v->shroudPositionFlat();
}

glm::vec3 Shroud::shroudPositionGlobe() const
{
  // TODO downcast!
  ShroudView* v = dynamic_cast<ShroudView*>(_view.get());
  return v->shroudPositionGlobe();
}
