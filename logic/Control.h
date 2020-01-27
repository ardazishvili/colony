#ifndef CONTROL_H
#define CONTROL_H

#include "../fig/Shader.h"
#include "AbstractStructureBuilder.h"
#include "AbstractUnitBuilder.h"
#include "Panel.h"
#include "TankFactory.h"

class Control
{
public:
  Control(Game* game,
          ColonyEventManager* eventManager,
          GLFWwindow* window,
          Shader& textureShader,
          Shader& linesShader,
          Terrain* terrain,
          AStar* router);
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
  Shader& _textureShader;
  Shader& _linesShader;
  AStar* _router;
};

#endif
