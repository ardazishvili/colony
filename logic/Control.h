#ifndef CONTROL_H
#define CONTROL_H

#include "../engine/Shader.h"
#include "AbstractStructureBuilder.h"
#include "AbstractUnitBuilder.h"
#include "Panel.h"
#include "TankFactory.h"

class Control
{
public:
  Control(Shader& shader);
  void display();
  void populateUnitPanel(Game& game, Buildable* buildable);
  void populateStructurePanel(Buildable* buildable);
  void clearUnitPanel();
  void clearStructurePanel();
  bool panelIsEmpty(Panel::Type type) const;

private:
  void addToUnitPanel(std::unique_ptr<AbstractUnitBuilder> builder);
  void addToStructurePanel(std::unique_ptr<AbstractStructureBuilder> builder);
  Panel _structurePanel;
  Panel _unitPanel;
  Shader& _shader;
};

#endif
