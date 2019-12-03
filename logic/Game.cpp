#include "../imgui/imgui.h"

#include "Game.h"
#include "EventManager.h"
#include "../globals.h"

#include <iostream>
#include <iomanip>

void Game::tick()
{
  for (auto& tank : _tanks) {
    if (tank->isDestroyed()) {
      tank->stopShooting();
    }

    if (tank->isShooting()) {
      tank->shootTarget();
    }

    if(tank->isMoving()) {
      tank->move();
    }
  }

  
  displayTanks();
  displayShells();
  displayStructures();
  displayControl();

  showDebug();
}

void Game::addTank(std::shared_ptr<Tank> tank)
{
  _tanks.push_back(tank);
}

void Game::addStructure(std::shared_ptr<BuildableStructure> buildable)
{
  _structures.push_back(buildable);
}

void Game::setControl(std::unique_ptr<Control> control)
{
  _control = std::move(control);
}

void Game::displayTanks()
{
  for (auto& tank : _tanks) {
    tank->display();
  }
}

void Game::displayShells()
{
  for(auto& tank : _tanks) {
    tank->updateShells();
  }
}

void Game::displayStructures()
{
  for(auto& structure : _structures) {
    structure->display();
  }
}

void Game::displayControl()
{
  _control->display();
}

Tank* Game::getTank(const glm::vec2& mousePoint, bool select)
{
  if(select) {
    for(auto& tank : _tanks) {
      if (!tank->isUnderFire()) {
        tank->deselect();
      }
    }
  }
  for(auto& tank : _tanks) {
    if (tank->isUnderCursor(mousePoint) && !tank->isDestroyed()) {
      if(select){
	tank->select();
      }
      _selectedTank = tank.get();
      return tank.get();
    }
  }

  _selectedTank = nullptr;
  return nullptr;
}

VehicleGroup Game::getTanks(glm::vec4 area)
{
  for(auto& tank : _tanks) {
    tank->deselect();
  }

  auto result = VehicleGroup();
  for(auto& tank : _tanks) {
    if (tank->isInsideArea(area) && !tank->isDestroyed()) {
      tank->select();
      result.add(tank.get());
    }
  }

  return result;
}

Buildable* Game::getStructure(const glm::vec2& mousePoint)
{
  for (auto& structure : _structures) {
    if (!structure->isUnderFire()) {
      structure->deselect();
    }
  }

  for(auto& structure : _structures) {
    if(structure->isUnderCursor(mousePoint) && !structure->isDestroyed()) {
      _selectedStructure = structure.get();
      structure->select();
      _control->populateUnitPanel(*this, _selectedStructure);
      _control->populateStructurePanel(_selectedStructure);
      return _selectedStructure;
    }
  }

  _selectedStructure = nullptr;
  return _selectedStructure;
}

void Game::showDebug()
{
  auto flags = ImGuiWindowFlags_NoTitleBar |
               ImGuiWindowFlags_NoResize |
      	 ImGuiWindowFlags_NoMove |
      	 ImGuiWindowFlags_NoScrollbar |
      	 ImGuiWindowFlags_NoSavedSettings |
      	 ImGuiWindowFlags_NoInputs;
  ImGui::Begin("3dCoordinates", NULL, flags);
  ImGui::SetWindowPos(ImVec2(0, screenHeight - 22));
  ImGui::SetWindowSize(ImVec2(250, 22));
  auto pos = EventManager::unProject(currentX, currentY);
  std::stringstream ss;
  ss << "x:" << std::setw(5) << std::setprecision(2) << pos.x << "; y:"<< std::setw(5) << std::setprecision(2) << pos.y << "; z: " << pos.z;
  ImGui::Text(ss.str().c_str());
  ImGui::End();
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
