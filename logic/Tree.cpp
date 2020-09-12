#include "Tree.h"

Tree::Tree(fig::Shader& shader, glm::vec3 position) :
  AbstractPlant(std::make_unique<TreeView>(shader, position))
{
}
