#pragma once

#include "fig/Beam.h"
#include "view/StructureView.h"

class TurbineView : public StructureView {
 public:
  TurbineView(glm::vec3 position, glm::vec3 shroudPositionFlat,
              glm::vec3 shroudPositionGlobe);
  void draw() override;
  void initBeam();

 private:
  Timer _timer;
  std::unique_ptr<fig::Beam> _beamFlat;
  std::unique_ptr<fig::Beam> _beamGlobe;
  glm::vec3 _shroudPosFlat;
  glm::vec3 _shroudPosGlobe;
  static constexpr float TURBINE_HEALTH_BAR_WIDTH = 1.2f;
  static constexpr float TURBINE_HEALTH_BAR_HEIGHT = 0.15f;
  static constexpr float TURBINE_SCALE_FACTOR = 0.4f;
  static constexpr float TURBINE_MODEL_HEIGHT = 5.7;
  static constexpr std::chrono::milliseconds TURBINE_CYCLE =
      std::chrono::milliseconds(30000);
};
