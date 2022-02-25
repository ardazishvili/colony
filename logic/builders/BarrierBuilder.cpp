#include "BarrierBuilder.h"

#include "figImpl/ColonyEventManager.h"
#include "logic/structures/Barrier.h"

BarrierBuilder::BarrierBuilder(ColonyEventManager* eventManager,
                               fig::Terrain& terrain, fig::AStar& astar)
    : AbstractStructureBuilder(eventManager),
      _terrain(terrain),
      _astar(astar) {}

void BarrierBuilder::addToGame(Game& game) {
  auto structure = std::make_shared<Barrier>(glm::vec3(), _terrain, _astar);
  game.addStructure(structure);
  game.addShroud(structure->shroud());
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures BarrierBuilder::getPreviewType() {
  return fig::MenuTextures::Barrier;
}
