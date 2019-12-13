#include "BarrierBuilder.h"
#include "Barrier.h"
#include "EventManager.h"
#include "Game.h"

BarrierBuilder::BarrierBuilder(Game* game,
                               EventManager* eventManager,
                               Shader& shader,
                               Terrain* terrain) :
  AbstractStructureBuilder(game, eventManager),
  _shader(shader), _terrain(terrain)
{
}

void BarrierBuilder::create()
{
  auto structure = std::make_shared<Barrier>(_shader, glm::vec3(), _terrain);
  _game->addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures BarrierBuilder::getPreviewType()
{
  return MenuTextures::Barrier;
}
