#include "TankFactoryBuilder.h"

#include "figImpl/ColonyEventManager.h"
#include "logic/Game.h"
#include "logic/structures/TankFactory.h"

TankFactoryBuilder::TankFactoryBuilder(ColonyEventManager* eventManager,
                                       fig::AStar& router)
    : AbstractStructureBuilder(eventManager), _router(router) {}

void TankFactoryBuilder::addToGame(Game& game) {
  auto structure = std::make_shared<TankFactory>(_router, glm::vec3());
  game.addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures TankFactoryBuilder::getPreviewType() {
  return fig::MenuTextures::TankFactory;
}

TankFactoryBuilder::~TankFactoryBuilder() {}
