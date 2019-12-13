#include <iostream>

#include <GL/glew.h>

#include "EventManager.h"
#include "Game.h"
#include "Hq.h"
#include "HqBuilder.h"

HqBuilder::HqBuilder(Game* game,
                     EventManager* eventManager,
                     Shader& shader,
                     Terrain* terrain) :
  AbstractStructureBuilder(game, eventManager),
  _shader(shader), _terrain(terrain)
{
}

void HqBuilder::create()
{
  std::cout << "hq builder create" << std::endl;
  auto structure =
    std::make_shared<Hq>(_game, _eventManager, _shader, glm::vec3(), _terrain);
  _game->addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures HqBuilder::getPreviewType()
{
  return MenuTextures::Hq;
}

HqBuilder::~HqBuilder()
{
}
