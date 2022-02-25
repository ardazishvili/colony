#include "logic/structures/Tree.h"

Tree::Tree(glm::vec3 position)
    : AbstractPlant(std::make_unique<TreeView>(position)) {}
