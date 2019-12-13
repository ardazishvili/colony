#include <iostream>

#include "Control.h"
#include "HqBuilder.h"
#include "TankFactoryBuilder.h"

Control::Control(Game* game,
                 EventManager* eventManager,
                 GLFWwindow* window,
                 Shader& shader,
                 Terrain* terrain) :
  _game(game),
  _eventManager(eventManager),
  _structurePanel(window, Panel::Type::Structures, shader),
  _unitPanel(window, Panel::Type::Units, shader), _shader(shader)
{
  std::unique_ptr<AbstractBuilder> hqBuilder =
    std::make_unique<HqBuilder>(_game, _eventManager, shader, terrain);
  auto hqPanelItem = std::make_unique<PanelItem>(std::move(hqBuilder));
  _structurePanel.addItem(std::move(hqPanelItem));
}

void Control::display()
{
  _structurePanel.display();
  _unitPanel.display();
}

void Control::populateStructurePanel(Buildable* buildable)
{
  clearStructurePanel();
  StructureBuilders builders = buildable->getStructureBuilders();
  for (auto& builder : builders) {
    addToStructurePanel(std::move(builder));
  }
}

void Control::populateUnitPanel(Game* game, Buildable* buildable)
{
  clearUnitPanel();
  UnitBuilders builders = buildable->getUnitBuilders(game);
  for (auto& builder : builders) {
    addToUnitPanel(std::move(builder));
  }
}

void Control::clearUnitPanel()
{
  _unitPanel.clear();
}

void Control::clearStructurePanel()
{
  _structurePanel.clear();
}

void Control::addToUnitPanel(std::unique_ptr<AbstractUnitBuilder> builder)
{
  auto panelItem = std::make_unique<PanelItem>(std::move(builder));
  _unitPanel.addItem(std::move(panelItem));
}

void Control::addToStructurePanel(
  std::unique_ptr<AbstractStructureBuilder> builder)
{
  auto panelItem = std::make_unique<PanelItem>(std::move(builder));
  _structurePanel.addItem(std::move(panelItem));
}

bool Control::panelIsEmpty(Panel::Type type) const
{
  if (type == Panel::Type::Units) {
    return _unitPanel.isEmpty();
  } else {
    return _structurePanel.isEmpty();
  }
}
