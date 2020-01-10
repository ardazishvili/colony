#ifndef ATTACKING_H
#define ATTACKING_H

#include <list>

#include "../view/AttackUnitView.h"
#include "Buildable.h"

using Shells = std::list<Shell>;
template<typename T>
class Attacking
{
public:
  Attacking(Shader& textureShader, Shell::Size sh, AttackUnitView* view);

  void shootTarget();
  void startShooting(Buildable* other);
  void stopShooting();
  bool isShooting();
  void updateShells();

private:
  bool isShellLoaded();
  float getTargetAngle();
  float getTargetDistance();
  void reload();

  Shader& _textureShader;
  Buildable* _target;
  AttackUnitView* _view;
  Timer _clock;
  Shell::Size _shellSize;
  Shells _shells;
  std::chrono::milliseconds _shellLoadTime{ 200 };
};

#endif
