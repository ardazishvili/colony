#include "BarrierBuilder.h"
#include "Barrier.h"
#include "EventManager.h"
#include "Game.h"

BarrierBuilder::BarrierBuilder(Game* game,
                               EventManager* eventManager,
                               Shader& textureShader,
                               Shader& linesShader,
                               Terrain* terrain) :
  AbstractStructureBuilder(game, eventManager, textureShader, linesShader),
  _terrain(terrain)
{
}

void BarrierBuilder::create()
{
  auto structure = std::make_shared<Barrier>(
    _textureShader, _linesShader, glm::vec3(), _terrain);
  _game->addStructure(structure);
  _game->addBarrier(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures BarrierBuilder::getPreviewType()
{
  return MenuTextures::Barrier;
}
