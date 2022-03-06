#include "TankFactoryBuilder.h"

#include <memory>

#include "figImpl/ColonyEventManager.h"
#include "logic/Game.h"
#include "logic/structures/TankFactory.h"

TankFactoryBuilder::TankFactoryBuilder(ColonyEventManager* eventManager,
                                       fig::AStar& router)
    : AbstractStructureBuilder(eventManager), _router(router) {}

void TankFactoryBuilder::addToGame(Game& game) {
  auto structure = std::make_unique<TankFactory>(_router, glm::vec3());

  _eventManager->setStructureToBuild(structure.get());
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);

  game.addStructure(std::move(structure));
}

fig::MenuTextures TankFactoryBuilder::getPreviewType() {
  return fig::MenuTextures::TankFactory;
}

TankFactoryBuilder::~TankFactoryBuilder() {}
