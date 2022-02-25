#pragma once

#include "fig/Surface.h"
#include "view/View.h"

enum class Status { None, Selected, UnderFire, Destroyed };

struct HealthBarParams {
  float xOffset;
  float yOffset;
  float width;
  float height;
};

class SelectableView : public View {
 public:
  SelectableView(glm::vec3 posidion, float selectionRadius,
                 HealthBarParams healthBarParams,
                 fig::TexturePackType texturesType);
  bool contain(glm::vec3 point) const;
  void setHealthBarScaleFactor(float factor);
  void setTexture(Status status);
  float angle() const;

 protected:
  virtual void showHealthBar() = 0;

  float _selectionRadius{0.0f};
  float _healthBarScaleFactor{1.0};
  fig::Surface _healthBar;
  fig::TexturePackType _texturesType;
};
