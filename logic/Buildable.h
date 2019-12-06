#ifndef BUILDABLE_H
#define BUILDABLE_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "AbstractStructureBuilder.h"
#include "AbstractUnitBuilder.h"
#include "Shell.h"

class Game;

using UnitBuilders = std::vector<std::unique_ptr<AbstractUnitBuilder>>;
using StructureBuilders =
  std::vector<std::unique_ptr<AbstractStructureBuilder>>;

enum class Status
{
  None,
  Selected,
  UnderFire,
  Destroyed
};

class Buildable
{
public:
  virtual bool isUnderCursor(const glm::vec3& mousePoint) = 0;
  virtual void display() = 0;
  virtual void select() = 0;
  virtual void deselect() = 0;
  virtual void takeDamage(Shell::Size shellSize) = 0;
  virtual glm::vec3 position() = 0;
  virtual UnitBuilders getUnitBuilders(Game& game) = 0;
  virtual StructureBuilders getStructureBuilders() = 0;
  bool isDestroyed() const;
  bool isUnderFire() const;

  virtual ~Buildable() = default;

protected:
  float _health;
  float _maxHealth;
  Status _status;

private:
  virtual void updateHealthBar() = 0;
};

#endif
