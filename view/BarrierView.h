#ifndef BARRER_VIEW_H
#define BARRER_VIEW_H

#include "../engine/Surface.h"
#include "../engine/Terrain.h"
#include "../logic/Buildable.h"
#include "SelectableView.h"

class BarrierView : public SelectableView
{
public:
  BarrierView(Shader& shader, glm::vec3 position, Terrain* terrain);
  void draw() override;
  void setTexture(Status status);
  float radius() const;

private:
  void showHealthBar();

  float _scaleFactor{ 1 };
  Terrain* _terrain;
  static float BARRIER_HEALTH_BAR_WIDTH;
  static float BARRIER_HEALTH_BAR_HEIGHT;
};

#endif
