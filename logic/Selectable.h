#ifndef SELECTABLE_H
#define SELECTABLE_H

#include "../engine/LinesObject.h"
#include "../view/SelectableView.h"

template<typename T>
class Selectable
{
public:
  Selectable(SelectableView* view);

  bool isUnderCursor(const glm::vec3& mousePoint);
  bool isInsideArea(Points area);
  void select();
  void deselect();

private:
  SelectableView* _view;
};

#endif
