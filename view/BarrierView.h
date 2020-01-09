#ifndef BARRIER_VIEW_H
#define BARRIER_VIEW_H

#include <future>

/* #include "../engine/Beam.h" */
#include "../engine/Terrain.h"
#include "StructureView.h"

class BarrierView : public StructureView
{
public:
  BarrierView(Shader& textureShader,
              Shader& linesShader,
              glm::vec3 position,
              Terrain* terrain);
  void draw() override;
  float radius() const;
  void grow(std::shared_ptr<LivingArea> area);

private:
  float _scaleFactor{ BARRIER_INIT_SCALE };
  Terrain* _terrain;
  Shader& _linesShader;
  std::future<void> _growFuture;
  static float BARRIER_HEALTH_BAR_WIDTH;
  static float BARRIER_HEALTH_BAR_HEIGHT;
  static float BARRIER_SCALE_INCREMENT;
  static float BARRIER_INIT_SCALE;
};

#endif
