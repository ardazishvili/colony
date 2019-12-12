#ifndef HQ_VIEW_H
#define HQ_VIEW_H

#include "StructureView.h"

class HqView : public StructureView
{
public:
  HqView(Shader& shader, glm::vec3 position);
  void draw() override;
  void rotate(float degreeAngle);
  void move(glm::vec3 position);
  float angle() const;

private:
  float _angle{ 0.0f };
  static float HQ_HEALTH_BAR_WIDTH;
  static float HQ_HEALTH_BAR_HEIGHT;
};

#endif
