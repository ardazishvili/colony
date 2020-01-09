#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include <GLFW/glfw3.h>

#include "../engine/Terrain.h"
#include "AbstractPlant.h"
#include "Barrier.h"
#include "Control.h"
#include "VehicleGroup.h"

class Tank;
class AbstractStructureBuilder;

using Tanks = std::vector<std::shared_ptr<Tank>>;
using Structures = std::vector<std::shared_ptr<BuildableStructure>>;
using Shrouds = std::vector<std::shared_ptr<Shroud>>;

class Game
{
public:
  Game(GLFWwindow* window, glm::mat4& view, glm::mat4& projection);
  void tick();
  void addTank(std::shared_ptr<Tank> tank);
  void addStructure(std::shared_ptr<BuildableStructure> buildable);
  /* void addBarrier(std::shared_ptr<Barrier> barrier); */
  void addShroud(std::shared_ptr<Shroud> shroud);
  void addPlant(std::shared_ptr<AbstractPlant> plant);
  void addTerrain(Terrain* terrain);
  void setControl(std::unique_ptr<Control> control);

  Tank* getTank(const glm::vec3& mousePoint, bool select = false);
  VehicleGroup getTanks(Points area);
  Buildable* getStructure(const glm::vec3& mousePoint);
  void showDebug();
  void clearPanel(Panel::Type type);
  bool panelIsEmpty(Panel::Type type);
  glm::vec3 getNearestShroudPositionFlat() const;
  glm::vec3 getNearestShroudPositionGlobe() const;
  void addBarrierPotential(EnergyStructure* es);

private:
  void displayTanks();
  void displayShells();
  void displayStructures();
  void displayPlants();
  void displayControl();

  GLFWwindow* _window;
  glm::mat4& _view;
  glm::mat4& _projection;
  Tanks _tanks;
  Structures _structures;
  /* std::shared_ptr<Barrier> _barrier; */
  Shrouds _shrouds;
  Plants _plants;
  std::unique_ptr<Control> _control;
  Tank* _selectedTank = nullptr;
  Buildable* _selectedStructure = nullptr;
  Buildable* _selectedBarrier = nullptr;
  Terrain* _terrain;
};

#endif
