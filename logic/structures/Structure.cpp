#include "logic/structures/Structure.h"

#include "logic/structures/GroundStructure.h"

template <typename T>
Structure<T>::Structure(StructureView* view) : _view(view) {}

template <typename T>
void Structure<T>::commit() {
  _stage = BuildStage::Done;
  this->wrapped().deselect();
}

template <typename T>
void Structure<T>::setAngle(float angle) {
  _view->rotate(angle);
}

template <typename T>
void Structure<T>::setPosition(glm::vec3 position) {
  _view->move(position);
}

template <typename T>
void Structure<T>::render() {
  _view->draw();
}

// instantiating
template class Structure<GroundStructure>;
