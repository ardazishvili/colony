#include "../../figImpl/ColonyEventManager.h"

#include "../Game.h"
#include "../Hq.h"
#include "HqBuilder.h"

HqBuilder::HqBuilder(Game* game,
                     ColonyEventManager* eventManager,
                     fig::Shader& textureShader,
                     fig::Shader& linesShader,
                     fig::Terrain* terrain,
                     fig::AStar* router) :
  AbstractStructureBuilder(game, eventManager, textureShader, linesShader),
  _terrain(terrain), _router(router)
{
}

void HqBuilder::create()
{
  auto structure =
    std::make_shared<Hq>(_game, _eventManager, _textureShader, _linesShader, _router, glm::vec3(), _terrain);
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
