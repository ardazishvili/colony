#ifndef TREE_H
#define TREE_H

#include "../../view/TreeView.h"
#include "AbstractPlant.h"

class Tree : public AbstractPlant
{
public:
  Tree(glm::vec3 position);
};

#endif
