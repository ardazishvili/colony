#include "BarrierBuilder.h"

#include <memory>

#include "figImpl/ColonyEventManager.h"
#include "logic/structures/Barrier.h"

BarrierBuilder::BarrierBuilder(ColonyEventManager* eventManager,
                               fig::Terrain& terrain, fig::AStar& astar)
    : AbstractStructureBuilder(eventManager),
      _terrain(terrain),
      _astar(astar) {}

void BarrierBuilder::addToGame(Game& game) {
  auto structure = std::make_unique<Barrier>(glm::vec3(), _terrain, _astar);

  _eventManager->setStructureToBuild(structure.get());
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);

  game.addShroud(structure->shroud());
  game.addStructure(std::move(structure));
}

fig::MenuTextures BarrierBuilder::getPreviewType() {
  return fig::MenuTextures::Barrier;
}
