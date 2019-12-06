#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <GLFW/glfw3.h>

#include "../engine/Camera.h"
#include "Game.h"
#include "Tank.h"

class EventManager
{
public:
  EventManager(GLFWwindow* window, Game& game, Camera& camera, Shader& shader);
  void tick();
  void handleKeyPress(GLFWwindow* window,
                      int key,
                      int scancode,
                      int action,
                      int mods);
  void handleMouseMove(GLFWwindow* window, double xpos, double ypos);
  void handleMousePressed(int button, int action);
  void handleMouseReleased();
  static glm::vec3 unProject(int xpos, int ypos);
  void setStructureToBuild(std::shared_ptr<BuildableStructure> structure);
  void setStructureToBuildStage(BuildStage stage);

private:
  void handleMousePressedLeft();
  void handleMousePressedRight();

  GLFWwindow* _window;
  Camera& _camera;
  Game& _game;
  Shader& _shader;
  /* Surface _selectionSurface; */
  glm::vec2 _selectionSurfaceBottonLeft;
  bool _selectionActive{ false };
  Tank* _tankSelected{ nullptr };
  VehicleGroup _tanksSelected;
  Tank* _tankUnderAttack{ nullptr };
  Buildable* _structureSelected{ nullptr };
  std::shared_ptr<BuildableStructure> _structureToBuild{ nullptr };
  BuildStage _structureToBuildStage;
  Buildable* _structureUnderAttack{ nullptr };
};

#endif
