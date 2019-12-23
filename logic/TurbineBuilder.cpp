#include "TurbineBuilder.h"
#include "EventManager.h"
#include "Game.h"
#include "Turbine.h"

TurbineBuilder::TurbineBuilder(Game* game,
                               EventManager* eventManager,
                               Shader& textureShader,
                               Shader& linesShader) :
  AbstractStructureBuilder(game, eventManager, textureShader, linesShader)
{
}

void TurbineBuilder::create()
{
  auto structure =
    std::make_shared<Turbine>(_textureShader, _linesShader, _game, glm::vec3());
  _game->addStructure(structure);
  _eventManager->setStructureToBuild(structure);
  _eventManager->setStructureToBuildStage(BuildStage::SetPosition);
}

MenuTextures TurbineBuilder::getPreviewType()
{
  return MenuTextures::Turbine;
}
