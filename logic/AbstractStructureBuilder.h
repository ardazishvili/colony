#ifndef ABSTRACT_STRUCTURE_BUILDER_H
#define ABSTRACT_STRUCTURE_BUILDER_H

#include "AbstractBuilder.h"

class ColonyEventManager;
class AbstractStructureBuilder : public AbstractBuilder
{
public:
  AbstractStructureBuilder(Game* game,
                           ColonyEventManager* eventManager,
                           Shader& textureShader,
                           Shader& linesShader) :
    AbstractBuilder(game),
    _eventManager(eventManager), _textureShader(textureShader),
    _linesShader(linesShader)
  {
  }
  virtual ~AbstractStructureBuilder() = default;

protected:
  ColonyEventManager* _eventManager;
  Shader& _textureShader;
  Shader& _linesShader;
};

#endif
