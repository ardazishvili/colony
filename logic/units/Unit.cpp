#include "logic/units/Unit.h"

#include "fig/globals.h"
#include "logic/units/AttackUnit.h"
#include "logic/units/NonAttackUnit.h"

template <typename T>
Unit<T>::Unit(fig::AStar& router, View* view) : _router(router), _view(view) {}

template <typename T>
void Unit<T>::render() {
  _view->draw();
  if (_path) {
    _path.value()->render();
  }
}

// instantiating
template class Unit<AttackUnit>;
template class Unit<NonAttackUnit>;
