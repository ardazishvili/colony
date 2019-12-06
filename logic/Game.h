#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "Control.h"
#include "VehicleGroup.h"

using Tanks = std::vector<std::shared_ptr<Tank>>;
using Structures = std::vector<std::shared_ptr<BuildableStructure>>;

class Tank;
class AbstractStructureBuilder;

class Game
{
public:
  Game() = default;
  void tick();
  void addTank(std::shared_ptr<Tank> tank);
  void addStructure(std::shared_ptr<BuildableStructure> buildable);
  void setControl(std::unique_ptr<Control> control);

  Tank* getTank(const glm::vec3& mousePoint, bool select = false);
  VehicleGroup getTanks(glm::vec4 area);
  Buildable* getStructure(const glm::vec3& mousePoint);
  void showDebug();
  void clearPanel(Panel::Type type);
  bool panelIsEmpty(Panel::Type type);

private:
  void displayTanks();
  void displayShells();
  void displayStructures();
  void displayControl();

  Tanks _tanks;
  Structures _structures;
  std::unique_ptr<Control> _control;
  Tank* _selectedTank = nullptr;
  Buildable* _selectedStructure = nullptr;
};

#endif
