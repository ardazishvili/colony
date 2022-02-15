#include "HqBuilder.h"

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
      std::make_shared<Hq>(_eventManager, _router, glm::vec3(), _terrain);
  game.addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures HqBuilder::getPreviewType() { return fig::MenuTextures::Hq; }

HqBuilder::~HqBuilder() {}
