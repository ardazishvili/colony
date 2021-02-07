#ifndef ABSTRACT_STRUCTURE_BUILDER_H
#define ABSTRACT_STRUCTURE_BUILDER_H

#include "AbstractBuilder.h"

class ColonyEventManager;
class AbstractStructureBuilder : public AbstractBuilder
{
public:
  AbstractStructureBuilder(Game* game,
                           ColonyEventManager* eventManager,
                           fig::Shader& textureShader,
                           fig::Shader& linesShader) :
    AbstractBuilder(game),
    _eventManager(eventManager), _textureShader(textureShader), _linesShader(linesShader)
  {
  }
  virtual ~AbstractStructureBuilder() = default;

protected:
  ColonyEventManager* _eventManager;
  fig::Shader& _textureShader;
  fig::Shader& _linesShader;
};

#endif
