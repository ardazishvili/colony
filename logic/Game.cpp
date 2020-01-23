#include "../imgui/imgui.h"

#include "../engine/Circle.h"
#include "../globals.h"
#include "../misc/Logger.h"
#include "EventManager.h"
#include "Game.h"

#include <iomanip>
#include <iostream>

Game::Game(glm::mat4& view, glm::mat4& projection) :
  _view(view), _projection(projection)
{
}

void Game::tick()
{
  for (auto& tank : _tanks) {
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

  displayTanks();
  displayShells();
  displayStructures();
  displayPlants();
  displayControl();
}

void Game::addTank(std::shared_ptr<Tank> tank)
{
  tank->setTerrain(_terrain);
  _tanks.push_back(tank);
}

void Game::addStructure(std::shared_ptr<GroundStructure> buildable)
{
  _structures.push_back(buildable);
}

void Game::addPlant(std::shared_ptr<AbstractPlant> plant)
{
  _plants.push_back(plant);
}

void Game::addShroud(std::shared_ptr<Shroud> shroud)
{
  _shrouds.push_back(shroud);
}

void Game::addTerrain(Terrain* terrain)
{
  _terrain = terrain;
}

void Game::setControl(std::unique_ptr<Control> control)
{
  _control = std::move(control);
}

void Game::displayTanks()
{
  for (auto& tank : _tanks) {
    tank->render();
  }
}

void Game::displayShells()
{
  for (auto& tank : _tanks) {
    tank->updateShells();
  }
}

void Game::displayStructures()
{
  for (auto& structure : _structures) {
    structure->render();
  }
}

void Game::displayPlants()
{
  for (auto& plant : _plants) {
    plant->render();
  }
}

void Game::displayControl()
{
  _control->display();
}

AttackUnit* Game::getAttackUnit(const glm::vec3& mousePoint, bool select)
{
  if (select) {
    for (auto& tank : _tanks) {
      if (!tank->isUnderFire()) {
        tank->deselect();
      }
    }
  }
  for (auto& tank : _tanks) {
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

VehicleGroup Game::getTanks(Points area)
{
  for (auto& tank : _tanks) {
    tank->deselect();
  }

  auto result = VehicleGroup();
  for (auto& tank : _tanks) {
    if (tank->isInsideArea(area) && !tank->isDestroyed()) {
      tank->select();
      result.add(tank.get());
    }
  }

  return result;
}

Buildable* Game::getStructure(const glm::vec3& mousePoint)
{
  for (auto& structure : _structures) {
    if (!structure->isUnderFire()) {
      structure->deselect();
    }
  }

  for (auto& structure : _structures) {
    if (structure->isUnderCursor(mousePoint) && !structure->isDestroyed()) {
      _selectedStructure = structure.get();
      structure->select();
      _control->populateUnitPanel(this, _selectedStructure);
      _control->populateStructurePanel(_selectedStructure);
      return _selectedStructure;
    }
  }

  _selectedStructure = nullptr;
  return _selectedStructure;
}

void Game::clearPanel(Panel::Type type)
{
  if (type == Panel::Type::Units) {
    _control->clearUnitPanel();
  } else {
    _control->clearStructurePanel();
  }
}

bool Game::panelIsEmpty(Panel::Type type)
{
  return _control->panelIsEmpty(type);
}

glm::vec3 Game::getNearestShroudPositionFlat(glm::vec3 p) const
{
  const Shroud* shroud = getNearestShroud(p);
  return getNearestShroud(p)->positionFlat();
}

glm::vec3 Game::getNearestShroudPositionGlobe(glm::vec3 p) const
{
  const Shroud* shroud = getNearestShroud(p);
  return getNearestShroud(p)->positionGlobe();
}

void Game::addBarrierPotential(EnergyStructure* es)
{
  getNearestShroud(es->position())->barrier().addEnergyStructure(es);
}

Shroud* Game::getNearestShroud(glm::vec3 p) const
{
  auto it = std::min_element(_shrouds.begin(),
                             _shrouds.end(),
                             [&p](const auto& left, const auto& right) {
                               return glm::distance(left->position(), p) <
                                      glm::distance(right->position(), p);
                             });
  return (*it).get();
}
