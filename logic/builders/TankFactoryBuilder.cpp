#include "../../figImpl/ColonyEventManager.h"

#include "../Game.h"
#include "../structures/TankFactory.h"
#include "TankFactoryBuilder.h"

TankFactoryBuilder::TankFactoryBuilder(Game* game, ColonyEventManager* eventManager, fig::AStar* router) :
  AbstractStructureBuilder(game, eventManager), _router(router)
{
}

void TankFactoryBuilder::create()
{
  auto structure = std::make_shared<TankFactory>(_router, glm::vec3());
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
