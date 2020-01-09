#include "Barrier.h"
#include "../globals.h"
#include "PlantBuilder.h"
#include "TreeBuilder.h"

const int Barrier::BARRIER_HP = 200;

Barrier::Barrier(Shader& textureShader,
                 Shader& linesShader,
                 glm::vec3 position,
                 Terrain* terrain,
                 AStar* router) :
  EnergyStructure(textureShader,
                  linesShader,
                  std::make_unique<BarrierView>(textureShader,
                                                linesShader,
                                                position,
                                                terrain)),
  _shroud(textureShader, linesShader, router, position), _terrain(terrain)
{

  _health = BARRIER_HP;
  _maxHealth = _health;
}

void Barrier::render()
{
  if (_stage == BuildStage::Done) {
    _shroud.render();
    if (_shroud.setUp()) {
      Buildable::render();
      if (_livingArea != nullptr) {
        if (_clock.elapsed() >= _bioUpdateTime) {
          logger.log("updating area...");
          _terrain->updateLivingArea(_livingArea);
          _clock.reload();
        }
      }
    }
  } else {
    Buildable::render();
  }
}

UnitBuilders Barrier::getUnitBuilders(Game* game)
{
  auto builders = UnitBuilders();
  std::unique_ptr<AbstractUnitBuilder> pb =
    std::make_unique<PlantBuilder>(_textureShader, game, *this, _terrain);
  builders.push_back(std::move(pb));

  std::unique_ptr<AbstractUnitBuilder> tb =
    std::make_unique<TreeBuilder>(_textureShader, game, *this, _terrain);
  builders.push_back(std::move(tb));

  return builders;
}

StructureBuilders Barrier::getStructureBuilders()
{
  return StructureBuilders();
}

void Barrier::addPlant(std::shared_ptr<AbstractPlant> p)
{
  std::cout << "p.x= " << p->position().x << std::endl;
  std::cout << "p.y= " << p->position().y << std::endl;
  _livingArea->plants.push_back(p->position());
  _plants.push_back(p);
}

void Barrier::commit()
{
  auto p = _view->position();
  // TODO downcast
  BarrierView* v = dynamic_cast<BarrierView*>(_view.get());
  CircularRegion r = { p.x, p.y, v->radius() };
  auto c = _terrain->getRgbColor(p.x, p.y);
  _livingArea = _terrain->addLivingArea(r, glm::vec4(c.x, c.y, c.z, 0.5));
  BuildableStructure::commit();
}

glm::vec3 Barrier::shroudPositionFlat() const
{
  return _shroud.positionFlat();
}

glm::vec3 Barrier::shroudPositionGlobe() const
{
  return _shroud.positionGlobe();
}

void Barrier::addEnergyStructure(EnergyStructure* es)
{
  _energyStructures.push_back(es);
  // TODO downcast
  BarrierView* v = dynamic_cast<BarrierView*>(_view.get());
  v->grow(_livingArea);
}

float Barrier::radius() const
{
  // TODO downcast
  BarrierView* v = dynamic_cast<BarrierView*>(_view.get());
  return v->radius();
}
