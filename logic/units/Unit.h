#pragma once

#include "fig/Path.h"
#include "helpers/crtp_helper.h"
#include "logic/concepts/Buildable.h"

template <typename T>
class Unit : public crtp<T, Unit> {
 public:
  Unit(fig::AStar& router, View* view);
  virtual ~Unit() = default;
  Unit(const Unit&) = delete;
  Unit(Unit&&) = delete;
  Unit& operator=(const Unit&) = delete;
  Unit& operator=(Unit&&) = delete;

  void render();

 protected:
  std::shared_ptr<fig::Path> _path;
  fig::AStar& _router;
  View* _view;
};
