#ifndef BARRIER_VIEW_H
#define BARRIER_VIEW_H

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
  void drawShroud();
  void drawBeam();
  bool shroudSetUp() const;
  float radius() const;
  glm::vec3 shroudPosition() const;

private:
  float _scaleFactor{ 1 };
  Terrain* _terrain;
  std::shared_ptr<Model> _shroudModel;
  Beam _beam;
  float _beamRotateSpeed{ 1.0f };
  float _shroudZ{ 0.0f };
  Shader& _linesShader;
  static const float SHROUD_UP_SPEED;
  static const float SHROUD_HEIGHT;
  static float BARRIER_HEALTH_BAR_WIDTH;
  static float BARRIER_HEALTH_BAR_HEIGHT;
};

#endif
