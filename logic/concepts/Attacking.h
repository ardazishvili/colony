#pragma once

#include <list>

#include "helpers/crtp_helper.h"
#include "logic/concepts/Buildable.h"
#include "view/AttackUnitView.h"

using Shells = std::list<Shell>;
template <typename T>
class Attacking : public crtp<T, Attacking> {
 public:
  Attacking(Shell::Size sh, AttackUnitView* view);
  virtual ~Attacking() = default;
  Attacking(const Attacking&) = delete;
  Attacking(Attacking&&) = delete;
  Attacking& operator=(const Attacking&) = delete;
  Attacking& operator=(Attacking&&) = delete;

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

  Buildable* _target;
  AttackUnitView* _view;
  Timer _clock;
  Shell::Size _shellSize;
  Shells _shells;
  std::chrono::milliseconds _shellLoadTime{200};
};
