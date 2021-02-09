#ifndef UNIT_H
#define UNIT_H

#include "../../fig/Path.h"

#include "../concepts/Buildable.h"
#include <memory>
#include <optional>

template<typename T>
class Unit
{
public:
  Unit(View* view);
  virtual ~Unit() = default;
  Unit(const Unit&) = delete;
  Unit(Unit&&) = delete;
  Unit& operator=(const Unit&) = delete;
  Unit& operator=(Unit&&) = delete;

  void render();

protected:
  std::optional<fig::Path> _path = std::nullopt;
  View* _view;
};

#endif
