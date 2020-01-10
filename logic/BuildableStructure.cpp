#include "BuildableStructure.h"
#include "GroundStructure.h"

template<typename T>
Structure<T>::Structure(StructureView* view) : _view(view)
{
}

template<typename T>
void Structure<T>::commit()
{
  _stage = BuildStage::Done;
  T* derived = static_cast<T*>(this);
  derived->deselect();
}

template<typename T>
void Structure<T>::setAngle(float angle)
{
  _view->rotate(angle);
}

template<typename T>
void Structure<T>::setPosition(glm::vec3 position)
{
  _view->move(position);
}

template<typename T>
void Structure<T>::render()
{
  _view->draw();
}

// instantiating
template class Structure<GroundStructure>;
