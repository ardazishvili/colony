#ifndef BARRIER_VIEW_H
#define BARRIER_VIEW_H

#include <future>

#include "../engine/Beam.h"
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
  /* void drawShroud(); */
  /* void drawBeam(); */
  /* bool shroudSetUp() const; */
  /* bool onOrbit() const; */
  float radius() const;
  /* glm::vec3 shroudPositionFlat() const; */
  /* glm::vec3 shroudPositionGlobe() const; */
  /* void startAnimation(); */
  void grow(std::shared_ptr<LivingArea> area);

private:
  float _scaleFactor{ BARRIER_INIT_SCALE };
  Terrain* _terrain;
  /* Timer _timer; */
  /* std::shared_ptr<Model> _shroudModel; */
  /* Beam _beamFlat; */
  /* Beam _beamGlobe; */
  /* float _beamRotateSpeed{ 1.0f }; */
  /* glm::vec3 _shroudPosGlobe{ 0.0f }; */
  /* glm::vec3 _shroudPosFlat{ 0.0f }; */
  /* static const glm::vec3 SHROUD_FLAT_OFFSET; */
  /* static const glm::vec3 SHROUD_GLOBE_OFFSET; */
  Shader& _linesShader;
  /* bool _animate{ false }; */
  /* bool _setUp{ false }; */
  std::future<void> _growFuture;
  /* static const float SHROUD_UP_SPEED; */
  /* static const std::chrono::milliseconds SHROUD_CYCLE; */
  static float BARRIER_HEALTH_BAR_WIDTH;
  static float BARRIER_HEALTH_BAR_HEIGHT;
  static float BARRIER_SCALE_INCREMENT;
  static float BARRIER_INIT_SCALE;
};

#endif
