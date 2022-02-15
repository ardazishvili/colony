#pragma once

#include "view/AbstractPlantView.h"

class PlantView : public AbstractPlantView {
 public:
  PlantView(glm::vec3 position);
  void draw() override;
};
