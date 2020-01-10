#include "BuildableUnit.h"
#include "../globals.h"
#include "BuildableAttackUnit.h"
#include "BuildableNonAttackUnit.h"

template<typename T>
Unit<T>::Unit(AStar* router, View* view) : _router(router), _view(view)
{
}

template<typename T>
void Unit<T>::render()
{
  _view->draw();
  if (_path != nullptr) {
    _path->render();
  }
}

// instantiating
template class Unit<BuildableAttackUnit>;
template class Unit<BuildableNonAttackUnit>;
