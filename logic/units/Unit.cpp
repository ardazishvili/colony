#include "../../fig/globals.h"

#include "AttackUnit.h"
#include "NonAttackUnit.h"
#include "Unit.h"

template<typename T>
Unit<T>::Unit(View* view) : _view(view)
{
}

template<typename T>
void Unit<T>::render()
{
  _view->draw();
  if (_path.has_value()) {
    _path.value().render();
  }
}

// instantiating
template class Unit<AttackUnit>;
template class Unit<NonAttackUnit>;
