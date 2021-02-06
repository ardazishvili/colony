#include "../figImpl/ColonyEventManager.h"

#include "Game.h"
#include "Turbine.h"
#include "TurbineBuilder.h"

TurbineBuilder::TurbineBuilder(Game* game,
                               ColonyEventManager* eventManager,
                               fig::Shader& textureShader,
                               fig::Shader& linesShader) :
  AbstractStructureBuilder(game, eventManager, textureShader, linesShader)
{
}

void TurbineBuilder::create()
{
  auto structure = std::make_shared<Turbine>(_textureShader, _linesShader, _game, glm::vec3());
  _game->addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

fig::MenuTextures TurbineBuilder::getPreviewType()
{
  return fig::MenuTextures::Turbine;
}
