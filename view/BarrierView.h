#pragma once

#include <future>

#include "fig/Terrain.h"
#include "view/StructureView.h"

class BarrierView : public StructureView {
 public:
  BarrierView(glm::vec3 position, fig::Terrain* terrain);
  void draw() override;
  float radius() const;
  void grow(std::shared_ptr<fig::LivingArea> area);

 private:
  float _scaleFactor{BARRIER_INIT_SCALE};
  fig::Terrain* _terrain;
  std::future<void> _growFuture;
  static float BARRIER_HEALTH_BAR_WIDTH;
  static float BARRIER_HEALTH_BAR_HEIGHT;
  static float BARRIER_SCALE_INCREMENT;
  static float BARRIER_INIT_SCALE;
};
