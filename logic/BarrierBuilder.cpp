#include "BarrierBuilder.h"
#include "../globals.h"
#include "Barrier.h"

BarrierBuilder::BarrierBuilder(Shader& shader, Terrain* terrain) :
  _shader(shader), _terrain(terrain)
{
}

void BarrierBuilder::create()
{
  auto structure = std::make_shared<Barrier>(_shader, glm::vec3(), _terrain);
  game->addStructure(structure);
  eventManager->setStructureToBuild(structure);
  eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures BarrierBuilder::getPreviewType()
{
  return MenuTextures::Barrier;
}
