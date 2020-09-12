#include "BarrierBuilder.h"
#include "../figImpl/ColonyEventManager.h"
#include "Barrier.h"
#include "Game.h"

BarrierBuilder::BarrierBuilder(Game* game,
                               ColonyEventManager* eventManager,
                               fig::Shader& textureShader,
                               fig::Shader& linesShader,
                               fig::Terrain* terrain,
                               fig::AStar* astar) :
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

fig::MenuTextures BarrierBuilder::getPreviewType()
{
  return fig::MenuTextures::Barrier;
}
