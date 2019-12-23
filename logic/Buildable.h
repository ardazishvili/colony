#ifndef BUILDABLE_H
#define BUILDABLE_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../view/SelectableView.h"
#include "AbstractStructureBuilder.h"
#include "AbstractUnitBuilder.h"
#include "Shell.h"

class Game;

using UnitBuilders = std::vector<std::unique_ptr<AbstractUnitBuilder>>;
using StructureBuilders =
  std::vector<std::unique_ptr<AbstractStructureBuilder>>;

class Buildable
{
public:
  Buildable(Shader& textureShader, Shader& linesShader);
  virtual bool isUnderCursor(const glm::vec3& mousePoint) = 0;
  virtual UnitBuilders getUnitBuilders(Game* game) = 0;
  virtual StructureBuilders getStructureBuilders() = 0;
  bool isDestroyed() const;
  bool isUnderFire() const;
  void select();
  void deselect();
  void takeDamage(Shell::Size shellSize);
  glm::vec3 position() const;
  virtual void render();

  virtual ~Buildable() = default;

protected:
  void updateHealthBar();
  float _health;
  float _maxHealth;
  Status _status;
  Shader& _textureShader;
  Shader& _linesShader;
  SelectableView* _viewPtr;
};

#endif
