#include <iostream>

#include "../globals.h"
#include "Hq.h"
#include "HqBuilder.h"

HqBuilder::HqBuilder(Game* game, Shader& shader, Terrain* terrain) :
  AbstractStructureBuilder(game), _shader(shader), _terrain(terrain)
{
}

void HqBuilder::create()
{
  std::cout << "hq builder create" << std::endl;
  auto structure = std::make_shared<Hq>(_game, _shader, glm::vec3(), _terrain);
  _game->addStructure(structure);
  eventManager->setStructureToBuild(structure);
  eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures HqBuilder::getPreviewType()
{
  return MenuTextures::Hq;
}

HqBuilder::~HqBuilder()
{
}
