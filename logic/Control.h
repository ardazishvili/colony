#pragma once

#include "fig/Terrain.h"
#include "fig/Window.h"
#include "fig/math/AStar.h"
#include "logic/Panel.h"
#include "logic/builders/AbstractStructureBuilder.h"
#include "logic/builders/AbstractUnitBuilder.h"

class GroundStructure;

class Control {
 public:
  Control(Game& game, ColonyEventManager* eventManager, fig::Window& window,
          fig::Terrain& terrain, fig::AStar& router);
  void display();
  void populateUnitPanel(Game& game, GroundStructure& buildable);
  void populateStructurePanel(GroundStructure& buildable);
  void clearUnitPanel();
  void clearStructurePanel();
  bool panelIsEmpty(Panel::Type type) const;

 private:
  void addToUnitPanel(std::unique_ptr<AbstractUnitBuilder> builder);
  void addToStructurePanel(std::unique_ptr<AbstractStructureBuilder> builder);

  Game& _game;
  ColonyEventManager* _eventManager;
  Panel _structurePanel;
  Panel _unitPanel;
};
