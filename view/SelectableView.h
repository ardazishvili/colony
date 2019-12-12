#ifndef SELECTABLE_VIEW_H
#define SELECTABLE_VIEW_H

#include "../engine/Surface.h"
#include "View.h"

struct HealthBarParams
{
  float xOffset;
  float yOffset;
  float width;
  float height;
};

class SelectableView : public View
{
public:
  SelectableView(Shader& shader,
                 glm::vec3 posidion,
                 float selectionRadius,
                 HealthBarParams healthBarParams);
  bool contain(glm::vec3 point) const;
  void setHealthBarScaleFactor(float factor);

protected:
  float _selectionRadius{ 0.0f };
  float _healthBarScaleFactor{ 1.0 };
  Surface _healthBar;
};

#endif
