#include <iostream>

#include "TankFactoryBuilder.h"
#include "TankFactory.h"
#include "../globals.h"

TankFactoryBuilder::TankFactoryBuilder(Shader& shader) :
	_shader(shader)
{
}

void TankFactoryBuilder::create() 
{
  std::cout << "factory builder create" << std::endl;
  auto structure = std::make_shared<TankFactory>(_shader, glm::vec2());
  game.addStructure(structure);
  eventManager->setStructureToBuild(structure);
  eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures TankFactoryBuilder::getPreviewType()
{
  return MenuTextures::TankFactory;
}

TankFactoryBuilder::~TankFactoryBuilder()
{
}
