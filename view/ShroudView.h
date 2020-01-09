#ifndef SHROUD_VIEW_H
#define SHROUD_VIEW_H

#include "../engine/Beam.h"
#include "UnitView.h"

class ShroudView : public UnitView
{
public:
  ShroudView(Shader& textureShader, Shader& linesShader, glm::vec3 position);
  // FIXME stubs for now
  void draw() override;
  void drawBeam();
  void move(glm::vec3 newPosition) override{};
  void rotateBody(float degreeAngle) override{};
  void rotateGun(float degreeAngle) override{};

  glm::vec3 shroudPositionFlat() const;
  glm::vec3 shroudPositionGlobe() const;
  void startAnimation();
  bool shroudSetUp() const;
  bool onOrbit() const;

private:
  std::shared_ptr<Model> _shroudModel;
  Timer _timer;
  bool _animate{ false };
  bool _setUp{ false };
  Beam _beamFlat;
  Beam _beamGlobe;
  glm::vec3 _shroudPosGlobe{ 0.0f };
  glm::vec3 _shroudPosFlat{ 0.0f };

  static float HEALTH_BAR_WIDTH;
  static float HEALTH_BAR_HEIGHT;
  static const std::chrono::milliseconds SHROUD_CYCLE;
  static const glm::vec3 SHROUD_FLAT_OFFSET;
  static const glm::vec3 SHROUD_GLOBE_OFFSET;
  static const float SHROUD_UP_SPEED;
};

#endif
