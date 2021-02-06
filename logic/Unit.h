#ifndef UNIT_H
#define UNIT_H

#include "../fig/Path.h"

#include "Buildable.h"

template<typename T>
class Unit
{
public:
  Unit(fig::AStar* router, View* view);
  virtual ~Unit() = default;
  Unit(const Unit&) = delete;
  Unit(Unit&&) = delete;
  Unit& operator=(const Unit&) = delete;
  Unit& operator=(Unit&&) = delete;

  void render();

protected:
  std::shared_ptr<fig::Path> _path;
  fig::AStar* _router;
  View* _view;
};

#endif
