#include "Control.h"
#include "builders/HqBuilder.h"
#include "builders/TankFactoryBuilder.h"

Control::Control(Game* game, ColonyEventManager* eventManager, fig::Window* window, fig::Terrain* terrain) :
  _game(game), _eventManager(eventManager), _structurePanel(window, Panel::Type::Structures),
  _unitPanel(window, Panel::Type::Units)
{
  std::unique_ptr<AbstractBuilder> hqBuilder = std::make_unique<HqBuilder>(_game, _eventManager, terrain);
  auto hqPanelItem = std::make_unique<PanelItem>(std::move(hqBuilder));
  _structurePanel.addItem(std::move(hqPanelItem));
}

void Control::display()
{
  _structurePanel.display();
  _unitPanel.display();
}

void Control::populateStructurePanel(GroundStructure* buildable)
{
  clearStructurePanel();
  StructureBuilders builders = buildable->getStructureBuilders();
  for (auto& builder : builders) {
    addToStructurePanel(std::move(builder));
  }
}

void Control::populateUnitPanel(Game* game, GroundStructure* buildable)
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

void Control::addToStructurePanel(std::unique_ptr<AbstractStructureBuilder> builder)
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
