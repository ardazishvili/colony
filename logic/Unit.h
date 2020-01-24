#ifndef UNIT_H
#define UNIT_H

#include "../fig/Path.h"
#include "Buildable.h"

template<typename T>
class Unit
{
public:
  Unit(AStar* router, View* view);
  virtual ~Unit() = default;
  Unit(const Unit&) = delete;
  Unit(Unit&&) = delete;
  Unit& operator=(const Unit&) = delete;
  Unit& operator=(Unit&&) = delete;

  void render();

protected:
  std::shared_ptr<Path> _path;
  AStar* _router;
  View* _view;
};

#endif
