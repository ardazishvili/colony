#ifndef ABSTRACT_STRUCTURE_BUILDER_H
#define ABSTRACT_STRUCTURE_BUILDER_H

#include "AbstractBuilder.h"

class EventManager;
class AbstractStructureBuilder : public AbstractBuilder
{
public:
  AbstractStructureBuilder(Game* game,
                           EventManager* eventManager,
                           Shader& textureShader,
                           Shader& linesShader) :
    AbstractBuilder(game),
    _eventManager(eventManager), _textureShader(textureShader),
    _linesShader(linesShader)
  {
  }
  virtual ~AbstractStructureBuilder() = default;

protected:
  EventManager* _eventManager;
  Shader& _textureShader;
  Shader& _linesShader;
};

#endif
