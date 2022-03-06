#include "logic/Game.h"

#include <bits/ranges_algo.h>
#include <bits/ranges_base.h>

#include <iterator>
#include <memory>
#include <nlohmann/detail/input/input_adapters.hpp>
#include <vector>

#include "helpers/templates.h"
#include "logic/concepts/Selectable.h"
#include "logic/structures/Barrier.h"
#include "logic/units/AttackUnit.h"
#include "logic/units/VehicleGroup.h"

void Game::tick() {
  for (auto& tank : _attack_units) {
    if (tank->isDestroyed()) {
      tank->stopShooting();
    }

    if (tank->isShooting()) {
      tank->shootTarget();
    }

    if (tank->isMoving()) {
      tank->move();
    }
  }

  render(_attack_units);
  render(_structures);
  render(_plants);
  _control->display();
}

void Game::addTank(std::unique_ptr<Tank> tank) {
  tank->setTerrain(*_terrain);
  _attack_units.push_back(std::move(tank));
}

void Game::addTankAndDestination(std::unique_ptr<Tank> tank,
                                 glm::vec3 destination) {
  tank->setTerrain(*_terrain);
  tank->setRoute(destination);
  _attack_units.push_back(std::move(tank));
}

void Game::addStructure(std::unique_ptr<GroundStructure> buildable) {
  _structures.push_back(std::move(buildable));
}

void Game::addPlant(std::shared_ptr<AbstractPlant> plant) {
  _plants.push_back(plant);
}

void Game::addShroud(std::unique_ptr<Shroud> shroud) {
  _shrouds.push_back(std::move(shroud));
}

void Game::addTerrain(fig::Terrain* terrain) { _terrain = terrain; }

void Game::setControl(std::unique_ptr<Control> control) {
  _control = std::move(control);
}

AttackUnit* Game::getAttackUnit(const glm::vec3& mousePoint, bool select) {
  if (select) {
    for (auto& tank : _attack_units) {
      if (!tank->isUnderFire()) {
        tank->deselect();
      }
    }
  }
  for (auto& tank : _attack_units) {
    if (tank->isUnderCursor(mousePoint) && !tank->isDestroyed()) {
      if (select) {
        tank->select();
      }
      _selectedAttackUnit = tank.get();
      return tank.get();
    }
  }

  _selectedAttackUnit = nullptr;
  return nullptr;
}

VehicleGroup Game::getVehicleGroup(fig::Points area) {
  deselect(_attack_units);

  auto f = [&area](const auto& unit) {
    return unit->isInsideArea(area) && !unit->isDestroyed();
  };
  VehicleGroup::Selected group;
  ranges::for_each(_attack_units, [f, &group](const auto& unit) {
    if (f(unit)) {
      group.push_back(unit.get());
    }
  });
  select(group);
  return VehicleGroup(group);
}

Buildable* Game::getStructure(const glm::vec3& mousePoint) {
  for (auto& structure : _structures) {
    if (!structure->isUnderFire()) {
      structure->deselect();
    }
  }

  for (auto& structure : _structures) {
    if (structure->isUnderCursor(mousePoint) && !structure->isDestroyed()) {
      _selectedStructure = structure.get();
      structure->select();
      _control->populateUnitPanel(*this, *_selectedStructure);
      _control->populateStructurePanel(*_selectedStructure);
      return _selectedStructure;
    }
  }

  _selectedStructure = nullptr;
  return _selectedStructure;
}

void Game::clearPanel(Panel::Type type) {
  if (type == Panel::Type::Units) {
    _control->clearUnitPanel();
  } else {
    _control->clearStructurePanel();
  }
}

bool Game::panelIsEmpty(Panel::Type type) {
  return _control->panelIsEmpty(type);
}

glm::vec3 Game::getNearestShroudPositionFlat(glm::vec3 p) const {
  return getNearestShroud(p)->positionFlat();
}

glm::vec3 Game::getNearestShroudPositionGlobe(glm::vec3 p) const {
  return getNearestShroud(p)->positionGlobe();
}

void Game::addBarrierPotential(EnergyStructure* es) {
  getNearestShroud(es->position())->barrier().addEnergyStructure(es);
}

Shroud* Game::getNearestShroud(glm::vec3 p) const {
  auto it = std::min_element(_shrouds.begin(), _shrouds.end(),
                             [&p](const auto& left, const auto& right) {
                               return glm::distance(left->position(), p) <
                                      glm::distance(right->position(), p);
                             });
  return (*it).get();
}
