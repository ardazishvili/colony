#ifndef SELECTABLE_VIEW_H
#define SELECTABLE_VIEW_H

#include "../engine/Surface.h"
/* #include "../logic/Buildable.h" */
#include "View.h"

enum class Status { None, Selected, UnderFire, Destroyed };

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
                 HealthBarParams healthBarParams,
                 TexturePackType texturesType);
  bool contain(glm::vec3 point) const;
  void setHealthBarScaleFactor(float factor);
  void setTexture(Status status);

protected:
  virtual void showHealthBar() = 0;

  float _selectionRadius{ 0.0f };
  float _healthBarScaleFactor{ 1.0 };
  Surface _healthBar;
  TexturePackType _texturesType;
};

#endif
