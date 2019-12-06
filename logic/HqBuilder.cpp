#include <iostream>

#include "../globals.h"
#include "Hq.h"
#include "HqBuilder.h"

HqBuilder::HqBuilder(Shader& shader) : _shader(shader) {}

void HqBuilder::create()
{
  std::cout << "hq builder create" << std::endl;
  auto structure = std::make_shared<Hq>(_shader, glm::vec2());
  game.addStructure(structure);
  eventManager->setStructureToBuild(structure);
  eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures HqBuilder::getPreviewType()
{
  return MenuTextures::Hq;
}

HqBuilder::~HqBuilder() {}
