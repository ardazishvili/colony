#ifndef TURBINE_VIEW_H
#define TURBINE_VIEW_H

#include "../fig/Beam.h"
#include "StructureView.h"

class TurbineView : public StructureView
{
public:
  TurbineView(fig::Shader& textureShader,
              fig::Shader& linesShader,
              glm::vec3 position,
              glm::vec3 shroudPositionFlat,
              glm::vec3 shroudPositionGlobe);
  void draw() override;
  void initBeam();

private:
  fig::Shader& _linesShader;
  Timer _timer;
  std::unique_ptr<fig::Beam> _beamFlat;
  std::unique_ptr<fig::Beam> _beamGlobe;
  glm::vec3 _shroudPosFlat;
  glm::vec3 _shroudPosGlobe;
  static std::chrono::milliseconds TURBINE_CYCLE;
  static float TURBINE_HEALTH_BAR_WIDTH;
  static float TURBINE_HEALTH_BAR_HEIGHT;
  static float TURBINE_SCALE_FACTOR;
  static float TURBINE_MODEL_HEIGHT;
};

#endif
