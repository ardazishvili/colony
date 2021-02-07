#ifndef SHROUD_VIEW_H
#define SHROUD_VIEW_H

#include "../fig/Beam.h"

#include "UnitView.h"

class ShroudView : public UnitView
{
public:
  ShroudView(glm::vec3 position, float barrierHeight);
  void draw() override;
  void drawBeam();
  void move(glm::vec3 newPosition) override{};
  void rotateBody(float degreeAngle) override{};

  glm::vec3 positionFlat() const;
  glm::vec3 positionGlobe() const;
  void startAnimation();
  bool setUp() const;
  bool onOrbit() const;

private:
  std::shared_ptr<fig::Model> _model;
  Timer _timer;
  bool _animate{ false };
  bool _setUp{ false };
  fig::Beam _beamFlat;
  fig::Beam _beamGlobe;
  glm::vec3 _posGlobe{ 0.0f };
  glm::vec3 _posFlat{ 0.0f };

  static float HEALTH_BAR_WIDTH;
  static float HEALTH_BAR_HEIGHT;
  static const std::chrono::milliseconds CYCLE;
  static const glm::vec3 FLAT_OFFSET;
  static const glm::vec3 GLOBE_OFFSET;
  static const float UP_SPEED;
};

#endif
