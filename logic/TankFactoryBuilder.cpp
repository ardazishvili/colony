#include <iostream>

#include "../globals.h"
#include "TankFactory.h"
#include "TankFactoryBuilder.h"

TankFactoryBuilder::TankFactoryBuilder(Shader& shader) : _shader(shader) {}

void TankFactoryBuilder::create()
{
  std::cout << "factory builder create" << std::endl;
  auto structure = std::make_shared<TankFactory>(_shader, glm::vec3());
  game.addStructure(structure);
  eventManager->setStructureToBuild(structure);
  eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures TankFactoryBuilder::getPreviewType()
{
  return MenuTextures::TankFactory;
}

TankFactoryBuilder::~TankFactoryBuilder() {}
