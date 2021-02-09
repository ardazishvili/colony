#include "BarrierBuilder.h"
#include "../../figImpl/ColonyEventManager.h"
#include "../Game.h"
#include "../structures/Barrier.h"

BarrierBuilder::BarrierBuilder(Game* game, ColonyEventManager* eventManager, fig::Terrain* terrain) :
  AbstractStructureBuilder(game, eventManager), _terrain(terrain)
{
}

void BarrierBuilder::create()
{
  auto structure = std::make_shared<Barrier>(glm::vec3(), _terrain);
  _game->addStructure(structure);
  _game->addShroud(structure->shroud());
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures BarrierBuilder::getPreviewType()
{
  return fig::MenuTextures::Barrier;
}
