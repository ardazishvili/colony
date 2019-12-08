#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "../engine/Terrain.h"
#include "Barrier.h"
#include "Control.h"
#include "Plant.h"
#include "VehicleGroup.h"

using Tanks = std::vector<std::shared_ptr<Tank>>;
using Structures = std::vector<std::shared_ptr<BuildableStructure>>;
using Plants = std::vector<std::shared_ptr<Plant>>;
using Barriers = std::vector<std::shared_ptr<Barrier>>;

class Tank;
class AbstractStructureBuilder;

class Game
{
public:
  Game() = default;
  void tick();
  void addTank(std::shared_ptr<Tank> tank);
  void addStructure(std::shared_ptr<BuildableStructure> buildable);
  void addPlant(std::shared_ptr<Plant> plant);
  void addBarrier(std::shared_ptr<Barrier> barrier);
  void addTerrain(Terrain* terrain);
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
  void displayPlants();
  void displayBarriers();
  void displayControl();

  Tanks _tanks;
  Structures _structures;
  Plants _plants;
  Barriers _barriers;
  std::unique_ptr<Control> _control;
  Tank* _selectedTank = nullptr;
  Buildable* _selectedStructure = nullptr;
  Terrain* _terrain;
};

#endif
