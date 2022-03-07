#include "HqBuilder.h"

#include <memory>

#include "figImpl/ColonyEventManager.h"
#include "logic/Game.h"
#include "logic/structures/Hq.h"

HqBuilder::HqBuilder(ColonyEventManager* eventManager, fig::Terrain& terrain,
                     fig::AStar& router)
    : AbstractStructureBuilder(eventManager),
      _terrain(terrain),
      _router(router) {}

void HqBuilder::addToGame(Game& game) {
  auto structure =
      std::make_unique<Hq>(_eventManager, _router, glm::vec3(), _terrain);

  _eventManager->setStructureToBuild(structure.get());
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);

  game.addStructure(std::move(structure));
}

fig::MenuTextures HqBuilder::getPreviewType() { return fig::MenuTextures::Hq; }

HqBuilder::~HqBuilder() {}
