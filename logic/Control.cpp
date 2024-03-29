#include "logic/Control.h"

#include <ranges>

#include "logic/builders/HqBuilder.h"
#include "logic/structures/GroundStructure.h"

namespace ranges = std::ranges;

Control::Control(Game& game, ColonyEventManager* eventManager,
                 fig::Window& window, fig::Terrain& terrain, fig::AStar& router)
    : _game(game),
      _eventManager(eventManager),
      _structurePanel(window, game, Panel::Type::Structures),
      _unitPanel(window, game, Panel::Type::Units) {
  auto hqPanelItem = std::make_unique<PanelItem>(
      std::make_unique<HqBuilder>(_eventManager, terrain, router));
  _structurePanel.addItem(std::move(hqPanelItem));
}

void Control::display() {
  _structurePanel.display();
  _unitPanel.display();
}

void Control::populateStructurePanel(GroundStructure& buildable) {
  clearStructurePanel();
  ranges::for_each(buildable.getStructureBuilders(), [this](auto& builder) {
    addToStructurePanel(std::move(builder));
  });
}

void Control::populateUnitPanel(Game& game, GroundStructure& buildable) {
  clearUnitPanel();
  ranges::for_each(buildable.getUnitBuilders(), [this](auto& builder) {
    addToUnitPanel(std::move(builder));
  });
}

void Control::clearUnitPanel() { _unitPanel.clear(); }

void Control::clearStructurePanel() { _structurePanel.clear(); }

void Control::addToUnitPanel(std::unique_ptr<AbstractUnitBuilder> builder) {
  _unitPanel.addItem(std::make_unique<PanelItem>(std::move(builder)));
}

void Control::addToStructurePanel(
    std::unique_ptr<AbstractStructureBuilder> builder) {
  _structurePanel.addItem(std::make_unique<PanelItem>(std::move(builder)));
}

bool Control::panelIsEmpty(Panel::Type type) const {
  return type == Panel::Type::Units ? _unitPanel.isEmpty()
                                    : _structurePanel.isEmpty();
}
