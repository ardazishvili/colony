#include "../../figImpl/ColonyEventManager.h"

#include "../Game.h"
#include "../structures/Hq.h"
#include "HqBuilder.h"

HqBuilder::HqBuilder(Game* game, ColonyEventManager* eventManager, fig::Terrain* terrain) :
  AbstractStructureBuilder(game, eventManager), _terrain(terrain)
{
}

void HqBuilder::create()
{
  auto structure = std::make_shared<Hq>(_game, _eventManager, glm::vec3(), _terrain);
  _game->addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures HqBuilder::getPreviewType()
{
  return fig::MenuTextures::Hq;
}

HqBuilder::~HqBuilder()
{
}
