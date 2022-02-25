#pragma once

#include "fig/LinesObject.h"
#include "helpers/crtp_helper.h"
#include "view/SelectableView.h"

template <typename T>
class Selectable : public crtp<T, Selectable> {
 public:
  Selectable(SelectableView* view);
  virtual ~Selectable() = default;
  Selectable(const Selectable&) = delete;
  Selectable(Selectable&&) = delete;
  Selectable& operator=(const Selectable&) = delete;
  Selectable& operator=(Selectable&&) = delete;

  bool isUnderCursor(const glm::vec3& mousePoint);
  bool isInsideArea(fig::Points area);
  void select();
  void deselect();

 private:
  SelectableView* _view;
};
