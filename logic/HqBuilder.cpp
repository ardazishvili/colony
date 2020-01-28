#include <iostream>

#include <GL/glew.h>

#include "../figImpl/ColonyEventManager.h"
#include "Game.h"
#include "Hq.h"
#include "HqBuilder.h"

HqBuilder::HqBuilder(Game* game,
                     ColonyEventManager* eventManager,
                     Shader& textureShader,
                     Shader& linesShader,
                     Terrain* terrain,
                     AStar* router) :
  AbstractStructureBuilder(game, eventManager, textureShader, linesShader),
  _terrain(terrain), _router(router)
{
}

void HqBuilder::create()
{
  auto structure = std::make_shared<Hq>(_game,
                                        _eventManager,
                                        _textureShader,
                                        _linesShader,
                                        _router,
                                        glm::vec3(),
                                        _terrain);
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
