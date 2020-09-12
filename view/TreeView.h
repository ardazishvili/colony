#ifndef TREE_VIEW_H
#define TREE_VIEW_H

#include "AbstractPlantView.h"

class TreeView : public AbstractPlantView
{
public:
  TreeView(fig::Shader& shader, glm::vec3 position);
  void draw() override;
};

#endif
