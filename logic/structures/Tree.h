#pragma once

#include "logic/structures/AbstractPlant.h"
#include "view/TreeView.h"

class Tree : public AbstractPlant {
 public:
  Tree(glm::vec3 position);
};
