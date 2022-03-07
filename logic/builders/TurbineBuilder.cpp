#include "TurbineBuilder.h"

#include <memory>

#include "figImpl/ColonyEventManager.h"
#include "logic/Game.h"
#include "logic/structures/Turbine.h"

TurbineBuilder::TurbineBuilder(ColonyEventManager* eventManager)
    : AbstractStructureBuilder(eventManager) {}

void TurbineBuilder::addToGame(Game& game) {
  auto structure = std::make_unique<Turbine>(game, glm::vec3());
  _eventManager->setStructureToBuild(structure.get());
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);

  game.addStructure(std::move(structure));
}

fig::MenuTextures TurbineBuilder::getPreviewType() {
  return fig::MenuTextures::Turbine;
}
