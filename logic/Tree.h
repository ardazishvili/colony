#ifndef TREE_H
#define TREE_H

#include <glm/glm.hpp>

#include "../view/TreeView.h"
#include "AbstractPlant.h"

class Tree : public AbstractPlant
{
public:
  Tree(Shader& shader, glm::vec3 position);
};

#endif
