#ifndef ABSTRACT_STRUCTURE_BUILDER_H
#define ABSTRACT_STRUCTURE_BUILDER_H

#include "../../figImpl/globals.h"

#include "AbstractBuilder.h"

class ColonyEventManager;
class AbstractStructureBuilder : public AbstractBuilder
{
public:
  AbstractStructureBuilder(Game* game, ColonyEventManager* eventManager) :
    AbstractBuilder(game), _eventManager(eventManager), _textureShader(*SHADERS_MAP[ShaderType::TEXTURE]),
    _linesShader(*SHADERS_MAP[ShaderType::LINES])
  {
  }
  virtual ~AbstractStructureBuilder() = default;

protected:
  ColonyEventManager* _eventManager;
  fig::Shader& _textureShader;
  fig::Shader& _linesShader;
};

#endif
