#include "BarrierBuilder.h"
#include "../figImpl/ColonyEventManager.h"
#include "Barrier.h"
#include "Game.h"

BarrierBuilder::BarrierBuilder(Game* game,
                               ColonyEventManager* eventManager,
                               Shader& textureShader,
                               Shader& linesShader,
                               Terrain* terrain,
                               AStar* astar) :
  AbstractStructureBuilder(game, eventManager, textureShader, linesShader),
  _terrain(terrain), _astar(astar)
{
}

void BarrierBuilder::create()
{
  auto structure = std::make_shared<Barrier>(
    _textureShader, _linesShader, glm::vec3(), _terrain, _astar);
  _game->addStructure(structure);
  _game->addShroud(structure->shroud());
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures BarrierBuilder::getPreviewType()
{
  return MenuTextures::Barrier;
}
