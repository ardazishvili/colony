#include "../../figImpl/ColonyEventManager.h"

#include "../Game.h"
#include "../structures/TankFactory.h"
#include "TankFactoryBuilder.h"

TankFactoryBuilder::TankFactoryBuilder(Game* game, ColonyEventManager* eventManager) :
  AbstractStructureBuilder(game, eventManager)
{
}

void TankFactoryBuilder::create()
{
  auto structure = std::make_shared<TankFactory>(glm::vec3());
  _game->addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures TankFactoryBuilder::getPreviewType()
{
  return fig::MenuTextures::TankFactory;
}

TankFactoryBuilder::~TankFactoryBuilder()
{
}
