#include <iostream>

#include <GL/glew.h>

#include "EventManager.h"
#include "Game.h"
#include "TankFactory.h"
#include "TankFactoryBuilder.h"

TankFactoryBuilder::TankFactoryBuilder(Game* game,
                                       EventManager* eventManager,
                                       Shader& shader) :
  AbstractStructureBuilder(game, eventManager),
  _shader(shader)
{
}

void TankFactoryBuilder::create()
{
  std::cout << "factory builder create" << std::endl;
  auto structure = std::make_shared<TankFactory>(_shader, glm::vec3());
  _game->addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures TankFactoryBuilder::getPreviewType()
{
  return MenuTextures::TankFactory;
}

TankFactoryBuilder::~TankFactoryBuilder()
{
}
