#include "../../figImpl/ColonyEventManager.h"

#include "../Game.h"
#include "../structures/Turbine.h"
#include "TurbineBuilder.h"

TurbineBuilder::TurbineBuilder(Game* game, ColonyEventManager* eventManager) :
  AbstractStructureBuilder(game, eventManager)
{
}

void TurbineBuilder::create()
{
  auto structure = std::make_shared<Turbine>(_game, glm::vec3());
  _game->addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures TurbineBuilder::getPreviewType()
{
  return fig::MenuTextures::Turbine;
}
