#ifndef HQ_VIEW_H
#define HQ_VIEW_H

#include "StructureView.h"

class HqView : public StructureView
{
public:
  HqView(fig::Shader& shader, glm::vec3 position);
  void draw() override;

private:
  static float HQ_HEALTH_BAR_WIDTH;
  static float HQ_HEALTH_BAR_HEIGHT;
};

#endif
