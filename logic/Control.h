#ifndef CONTROL_H
#define CONTROL_H

#include "../fig/Window.h"
#include "../fig/shader/Shader.h"

#include "Panel.h"
#include "TankFactory.h"
#include "builders/AbstractStructureBuilder.h"
#include "builders/AbstractUnitBuilder.h"

class Control
{
public:
  Control(Game* game,
          ColonyEventManager* eventManager,
          fig::Window* window,
          fig::Shader& textureShader,
          fig::Shader& linesShader,
          fig::Terrain* terrain,
          fig::AStar* router);
  void display();
  void populateUnitPanel(Game* game, GroundStructure* buildable);
  void populateStructurePanel(GroundStructure* buildable);
  void clearUnitPanel();
  void clearStructurePanel();
  bool panelIsEmpty(Panel::Type type) const;

private:
  void addToUnitPanel(std::unique_ptr<AbstractUnitBuilder> builder);
  void addToStructurePanel(std::unique_ptr<AbstractStructureBuilder> builder);

  Game* _game;
  ColonyEventManager* _eventManager;
  Panel _structurePanel;
  Panel _unitPanel;
  fig::Shader& _textureShader;
  fig::Shader& _linesShader;
  fig::AStar* _router;
};

#endif
