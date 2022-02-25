#include "TurbineBuilder.h"

#include "figImpl/ColonyEventManager.h"
#include "logic/Game.h"
#include "logic/structures/Turbine.h"

TurbineBuilder::TurbineBuilder(ColonyEventManager* eventManager)
    : AbstractStructureBuilder(eventManager) {}

void TurbineBuilder::addToGame(Game& game) {
  auto structure = std::make_shared<Turbine>(game, glm::vec3());
  game.addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures TurbineBuilder::getPreviewType() {
  return fig::MenuTextures::Turbine;
}
