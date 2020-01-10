#include "Selectable.h"
#include "AttackUnit.h"
#include "GroundStructure.h"

template<typename T>
Selectable<T>::Selectable(SelectableView* view) : _view(view)
{
}

template<typename T>
void Selectable<T>::select()
{
  T* derived = static_cast<T*>(this);
  derived->_status = Status::Selected;
  _view->setTexture(Status::Selected);
}

template<typename T>
void Selectable<T>::deselect()
{
  T* derived = static_cast<T*>(this);
  if (derived->_status != Status::Destroyed) {
    derived->_status = Status::None;
    _view->setTexture(Status::None);
  }
}

template<typename T>
bool Selectable<T>::isUnderCursor(const glm::vec3& mousePoint)
{
  return _view->contain(mousePoint);
}

template<typename T>
bool Selectable<T>::isInsideArea(Points area)
{
  auto tmp = _view->position();
  auto m = glm::vec2(tmp.x, tmp.y);
  auto a = glm::vec2(area.at(0).x, area.at(0).y);
  auto b = glm::vec2(area.at(1).x, area.at(1).y);
  auto d = glm::vec2(area.at(3).x, area.at(3).y);
  glm::vec2 am = m - a;
  glm::vec2 ab = b - a;
  glm::vec2 ad = d - a;
  const bool cond1 =
    (0.0f < glm::dot(am, ab)) && (glm::dot(am, ab) < glm::dot(ab, ab));
  const bool cond2 =
    (0.0f < glm::dot(am, ad)) && (glm::dot(am, ad) < glm::dot(ad, ad));
  return cond1 && cond2;
}

// instantiating
template class Selectable<AttackUnit>;
template class Selectable<GroundStructure>;
