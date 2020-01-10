#ifndef UNIT_H
#define UNIT_H

#include "../engine/Path.h"
#include "../math/AStar.h"
#include "Buildable.h"

template<typename T>
class Unit
{
public:
  Unit(AStar* router, View* view);
  void render();

protected:
  std::shared_ptr<Path> _path;
  AStar* _router;
  View* _view;
};

#endif
