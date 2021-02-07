#ifndef CONTROL_H
#define CONTROL_H

#include "../fig/Window.h"

#include "Panel.h"
#include "builders/AbstractStructureBuilder.h"
#include "builders/AbstractUnitBuilder.h"
#include "structures/TankFactory.h"

class Control
{
public:
  Control(Game* game, ColonyEventManager* eventManager, fig::Window* window, fig::Terrain* terrain, fig::AStar* router);
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
  fig::AStar* _router;
};

#endif
