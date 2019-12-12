#include "Barrier.h"
#include "PlantBuilder.h"

Barrier::Barrier(Shader& textureShader, glm::vec3 position, Terrain* terrain) :
  _textureShader(textureShader), _view(textureShader, position, terrain),
  _terrain(terrain)
{
  CircularRegion r = { position.x, position.y, _view.radius() };
  auto c = terrain->getRgbColor(position.x, position.y);
  _livingArea = terrain->addLivingArea(r, glm::vec4(c.x, c.y, c.z, 0.5));
}

void Barrier::render()
{
  if (_clock.elapsed() >= _bioUpdateTime) {
    std::cout << "_plants.size()= " << _plants.size() << std::endl;
    _terrain->updateLivingArea(_livingArea);
    _clock.reload();
  }
  _view.draw();
}

bool Barrier::isUnderCursor(const glm::vec3& mousePoint)
{
  return _view.contain(mousePoint);
}

void Barrier::select()
{
  _view.setTexture(Status::Selected);
}

void Barrier::deselect()
{
  if (_status != Status::Destroyed) {
    _status = Status::None;
    _view.setTexture(Status::None);
  }
}

void Barrier::takeDamage(Shell::Size shellSize)
{
  if (_status != Status::Destroyed) {
    _status = Status::UnderFire;
    _view.setTexture(Status::UnderFire);
    _health =
      std::max(0.0f, _health - Shell::SHELL_DAMAGE_MAP.find(shellSize)->second);
    if (_health == 0) {
      _status = Status::Destroyed;
      _view.setTexture(Status::Destroyed);
    }
    updateHealthBar();
  }
}

glm::vec3 Barrier::position()
{
  return _view.position();
}

UnitBuilders Barrier::getUnitBuilders(Game& game)
{
  auto builders = UnitBuilders();
  std::unique_ptr<AbstractUnitBuilder> builder =
    std::make_unique<PlantBuilder>(_textureShader, game, *this, _terrain);
  builders.push_back(std::move(builder));

  return builders;
}

StructureBuilders Barrier::getStructureBuilders()
{
  return StructureBuilders();
}

void Barrier::updateHealthBar()
{
  auto factor = _health / _maxHealth;
  _view.setHealthBarScaleFactor(factor);
}

void Barrier::addPlant(std::shared_ptr<Plant> p)
{
  _livingArea->plants.push_back(p->position());
  _plants.push_back(p);
}
