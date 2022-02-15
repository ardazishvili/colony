#pragma once

#include "view/View.h"

class AbstractPlantView : public View {
 public:
  AbstractPlantView(glm::vec3 position);
  virtual void draw();
};
