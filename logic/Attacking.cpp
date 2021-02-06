#include "Attacking.h"
#include "AttackUnit.h"

template<typename T>
Attacking<T>::Attacking(fig::Shader& textureShader, Shell::Size sh, AttackUnitView* view) :
  _textureShader(textureShader), _shellSize(sh), _view(view)
{
  _target = nullptr;
  reload();
}

template<typename T>
void Attacking<T>::shootTarget()
{
  if (!isShellLoaded()) {
    return;
  }
  if (_target->isDestroyed()) {
    stopShooting();
    return;
  }

  float angle = getTargetAngle() + 90.0f;
  std::cout << "_view= " << _view << std::endl;
  _view->rotateGun(getTargetAngle());
  // TODO magic number = tank length
  _shells.emplace_back(_textureShader,
                       glm::vec3(_view->position().x, _view->position().y, 0.5f),
                       glm::radians(angle),
                       getTargetDistance(),
                       _shellSize);
  _target->takeDamage(_shellSize);
  reload();
}

template<typename T>
bool Attacking<T>::isShooting()
{
  return _target != nullptr;
}

template<typename T>
void Attacking<T>::startShooting(Buildable* other)
{
  T* derived = static_cast<T*>(this);
  if (other == derived) {
    return;
  }
  _target = other;
}

template<typename T>
void Attacking<T>::stopShooting()
{
  _target = nullptr;
}

template<typename T>
bool Attacking<T>::isShellLoaded()
{
  return _clock.elapsed() >= _shellLoadTime;
}

template<typename T>
float Attacking<T>::getTargetAngle()
{
  float targetX = _target->position().x;
  float targetY = _target->position().y;
  T& derived = static_cast<T&>(*this);
  float thisX = derived.position().x;
  float thisY = derived.position().y;
  float radianAngle = ::atan((targetY - thisY) / (targetX - thisX));
  float degreeAngle = radianAngle * 180.0f / M_PI;
  if (targetX - thisX < 0) {
    degreeAngle += 180.0f;
  }

  return degreeAngle;
}

template<typename T>
float Attacking<T>::getTargetDistance()
{
  float targetX = _target->position().x;
  float targetY = _target->position().y;
  T& derived = static_cast<T&>(*this);
  float thisX = derived.position().x;
  float thisY = derived.position().y;
  return ::sqrt(::pow(targetX - thisX, 2) + ::pow(targetY - thisY, 2));
}

template<typename T>
void Attacking<T>::reload()
{
  _clock.reload();
}

template<typename T>
void Attacking<T>::updateShells()
{
  bool pop = false;
  for (auto& shell : _shells) {
    if (shell.isDone()) {
      pop = true;
    }
    shell.update();
  }
  if (pop) {
    _shells.pop_front();
  }
}

// instantiating
template class Attacking<AttackUnit>;
