#ifndef TURBINE_VIEW_H
#define TURBINE_VIEW_H

#include "StructureView.h"

class TurbineView : public StructureView
{
public:
  TurbineView(Shader& textureShader, Shader& linesShader, glm::vec3 position);
  void draw() override;

private:
  Shader& _linesShader;
  static float TURBINE_HEALTH_BAR_WIDTH;
  static float TURBINE_HEALTH_BAR_HEIGHT;
};

#endif
