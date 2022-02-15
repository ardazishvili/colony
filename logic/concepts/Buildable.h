#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "logic/Shell.h"
#include "logic/builders/AbstractStructureBuilder.h"
#include "logic/builders/AbstractUnitBuilder.h"
#include "view/SelectableView.h"

class Game;

using UnitBuilders = std::vector<std::unique_ptr<AbstractUnitBuilder>>;
using StructureBuilders =
    std::vector<std::unique_ptr<AbstractStructureBuilder>>;

class Buildable {
 public:
  Buildable(SelectableView* view);
  bool isDestroyed() const;
  bool isUnderFire() const;
  void takeDamage(Shell::Size shellSize);
  glm::vec3 position() const;
  virtual void render() = 0;

  virtual ~Buildable() = default;
  Buildable(const Buildable&) = delete;
  Buildable(Buildable&&) = delete;
  Buildable& operator=(const Buildable&) = delete;
  Buildable& operator=(Buildable&&) = delete;

 protected:
  void updateHealthBar();
  float _health;
  float _maxHealth;
  Status _status;
  SelectableView* _view;
};
