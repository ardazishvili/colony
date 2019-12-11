#include "Barrier.h"
#include "PlantBuilder.h"

Barrier::Barrier(Shader& textureShader,
                 Shader& colorShader,
                 glm::vec3 position,
                 Terrain* terrain) :
  _textureShader(textureShader),
  _view(textureShader, colorShader, position, terrain)
{}

void Barrier::render()
{
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
    std::make_unique<PlantBuilder>(_textureShader, game, *this);
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
