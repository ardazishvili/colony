#pragma once

#include "view/AbstractPlantView.h"

class TreeView : public AbstractPlantView {
 public:
  TreeView(glm::vec3 position);
  void draw() override;
};
