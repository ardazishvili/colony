#ifndef BARRIER_VIEW_H
#define BARRIER_VIEW_H

#include "../engine/Terrain.h"
#include "StructureView.h"

class BarrierView : public StructureView
{
public:
  BarrierView(Shader& shader, glm::vec3 position, Terrain* terrain);
  void draw() override;
  void drawShroud();
  bool shroudSetUp() const;
  float radius() const;

private:
  float _scaleFactor{ 1 };
  Terrain* _terrain;
  std::shared_ptr<Model> _shroudModel;
  float _shroudZ{ 0.0f };
  static const float SHROUD_UP_SPEED;
  static const float SHROUD_HEIGHT;
  static float BARRIER_HEALTH_BAR_WIDTH;
  static float BARRIER_HEALTH_BAR_HEIGHT;
};

#endif
