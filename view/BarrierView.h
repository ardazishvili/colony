#ifndef BARRIER_VIEW_H
#define BARRIER_VIEW_H

#include "../engine/Terrain.h"
#include "StructureView.h"

class BarrierView : public StructureView
{
public:
  BarrierView(Shader& shader, glm::vec3 position, Terrain* terrain);
  void draw() override;
  float radius() const;

private:
  float _scaleFactor{ 1 };
  Terrain* _terrain;
  static float BARRIER_HEALTH_BAR_WIDTH;
  static float BARRIER_HEALTH_BAR_HEIGHT;
};

#endif
