#include "logic/concepts/Moving.h"

#include "logic/units/AttackUnit.h"

template <typename T>
const float Moving<T>::MOVE_STOP_TOL = 0.02;

template <typename T>
Moving<T>::Moving(UnitView* view, float speed)
    : _view(view), _speed(speed), _destination(-1, -1) {}

template <typename T>
void Moving<T>::move() {
  auto prev = _view->position();
  auto c = _terrain->getXYZ(glm::vec2(prev.x, prev.y) + _moveIncrement);
  _view->move(c);
  bool destinationIsReached =
      ::sqrt(::pow(_view->position().x - _destination.x, 2) +
             ::pow(_view->position().y - _destination.y, 2)) < _speed;
  T& wrapped = this->wrapped();
  if (destinationIsReached || wrapped.isDestroyed()) {
    _movingRoute.pop_back();
    wrapped._path.value()->popLine();
    if (!_movingRoute.empty()) {
      startMoving(_movingRoute.at(_movingRoute.size() - 1));
    } else {
      stopMoving();
    }
  }
}

template <typename T>
void Moving<T>::setRoute(glm::vec3 endPoint) {
  T& wrapped = this->wrapped();
  wrapped._path = fig::makePath(*SHADERS_MAP[ShaderType::LINES],
                                wrapped._router, _view->position(), endPoint);
  if (wrapped._path.has_value()) {
    _movingRoute = wrapped._path.value()->route();
    startMoving(_movingRoute.at(_movingRoute.size() - 1));
  } else {
    std::cout << "No path to endpoint!" << std::endl;
  }
}

template <typename T>
void Moving<T>::startMoving(glm::vec2 endPoint) {
  _destination = glm::vec2(endPoint.x, endPoint.y);

  float dy = _destination.y - _view->position().y;
  float dx = _destination.x - _view->position().x;
  float radianAngle = ::atan(dx / dy);
  if (dy < 0) {
    radianAngle += M_PI;
  }
  float degreeAngle = radianAngle * 180.0f / M_PI - 90;
  _view->rotateBody(degreeAngle);
  _moveIncrement.x = _speed * ::sin(radianAngle);
  _moveIncrement.y = _speed * ::cos(radianAngle);
}

template <typename T>
void Moving<T>::stopMoving() {
  _destination = glm::vec3(-1, -1, -1);
  T& wrapped = this->wrapped();
  wrapped._path.reset();
}

template <typename T>
bool Moving<T>::isMoving() {
  return _destination != glm::vec2(-1, -1);
}

template <typename T>
void Moving<T>::setTerrain(fig::Terrain& terrain) {
  _terrain = &terrain;
}

// instantiatiating
template class Moving<AttackUnit>;
