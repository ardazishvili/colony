#include "Barrier.h"
#include "PlantBuilder.h"
const int Barrier::BARRIER_HP = 200;

Barrier::Barrier(Shader& shader, glm::vec3 position, Terrain* terrain) :
  BuildableStructure(shader,
                     std::make_unique<BarrierView>(shader, position, terrain)),
  _terrain(terrain)
{
  std::cout << "position.x= " << position.x << std::endl;
  std::cout << "position.y= " << position.y << std::endl;

  _health = BARRIER_HP;
  _maxHealth = _health;
}

void Barrier::render()
{
  if (_livingArea != nullptr) {
    if (_clock.elapsed() >= _bioUpdateTime) {
      std::cout << "_plants.size()= " << _plants.size() << std::endl;
      _terrain->updateLivingArea(_livingArea);
      _clock.reload();
    }
  }
  Buildable::render();
}

UnitBuilders Barrier::getUnitBuilders(Game& game)
{
  auto builders = UnitBuilders();
  std::unique_ptr<AbstractUnitBuilder> builder =
    std::make_unique<PlantBuilder>(_shader, game, *this, _terrain);
  builders.push_back(std::move(builder));

  return builders;
}

StructureBuilders Barrier::getStructureBuilders()
{
  return StructureBuilders();
}

void Barrier::addPlant(std::shared_ptr<Plant> p)
{
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
