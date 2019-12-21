#include "Tree.h"

Tree::Tree(Shader& shader, glm::vec3 position) :
  AbstractPlant(std::make_unique<TreeView>(shader, position))
{
}
