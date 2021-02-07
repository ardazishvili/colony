#include "../../fig/globals.h"

#include "../builders/PlantBuilder.h"
#include "../builders/TreeBuilder.h"
#include "Barrier.h"

const int Barrier::BARRIER_HP = 200;

Barrier::Barrier(fig::Shader& textureShader,
                 fig::Shader& linesShader,
                 glm::vec3 position,
                 fig::Terrain* terrain,
                 fig::AStar* router) :
  EnergyStructure(textureShader,
                  linesShader,
                  std::make_unique<BarrierView>(textureShader, linesShader, position, terrain)),
  _shroud(textureShader, linesShader, router, position, *this), _terrain(terrain)
{

  _health = BARRIER_HP;
  _maxHealth = _health;
}

void Barrier::render()
{
  if (_stage == BuildStage::Done) {
    _shroud.render();
    if (_shroud.setUp()) {
      Structure<GroundStructure>::render();
      if (_livingArea != nullptr) {
        if (_clock.elapsed() >= _bioUpdateTime) {
          fig::logger.log("updating area...");
          _terrain->updateLivingArea(_livingArea);
          _clock.reload();
        }
      }
    }
  } else {
    Structure<GroundStructure>::render();
  }
}

UnitBuilders Barrier::getUnitBuilders(Game* game)
{
  auto builders = UnitBuilders();
  std::unique_ptr<AbstractUnitBuilder> pb = std::make_unique<PlantBuilder>(_textureShader, game, *this, _terrain);
  builders.push_back(std::move(pb));

  std::unique_ptr<AbstractUnitBuilder> tb = std::make_unique<TreeBuilder>(_textureShader, game, *this, _terrain);
  builders.push_back(std::move(tb));

  return builders;
}

StructureBuilders Barrier::getStructureBuilders()
{
  return StructureBuilders();
}

void Barrier::addPlant(std::shared_ptr<AbstractPlant> p)
{
  _livingArea->plants.push_back(p->position());
  _plants.push_back(p);
}

void Barrier::commit()
{
  auto p = _view->position();
  // TODO downcast
  BarrierView* v = dynamic_cast<BarrierView*>(_view.get());
  fig::CircularRegion r = { p.x, p.y, v->radius() };
  auto c = _terrain->getRgbColor(p.x, p.y);
  _livingArea = _terrain->addLivingArea(r, glm::vec4(c.x, c.y, c.z, 0.5));
  Structure<GroundStructure>::commit();
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

std::shared_ptr<Shroud> Barrier::shroud()
{
  return std::shared_ptr<Shroud>(&_shroud);
}
