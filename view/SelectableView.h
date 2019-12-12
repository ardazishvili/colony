#ifndef SELECTABLE_VIEW_H
#define SELECTABLE_VIEW_H

#include "View.h"

class SelectableView : public View
{
public:
  SelectableView(Shader& shader, glm::vec3 posidion, float selectionRadius);
  bool contain(glm::vec3 point) const;

protected:
  float _selectionRadius{ 0.0f };
};

#endif
