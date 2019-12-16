#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <GLFW/glfw3.h>

#include "../engine/Camera.h"
#include "Game.h"
#include "Tank.h"

class EventManager
{
public:
  EventManager(glm::mat4& view,
               glm::mat4& projection,
               GLFWwindow* window,
               Game* game,
               Camera& camera,
               Shader& textureShader,
               Shader& colorShader,
               Shader& linesShader,
               Terrain* terrain);
  void tick();
  void handleKeyPress(GLFWwindow* window,
                      int key,
                      int scancode,
                      int action,
                      int mods);
  void handleMouseMove(GLFWwindow* window, double xpos, double ypos);
  void handleMousePressed(int button, int action);
  void handleMouseReleased();
  static glm::vec3 unProject(GLFWwindow* window,
                             glm::mat4& view,
                             glm::mat4& proj);
  void setStructureToBuild(std::shared_ptr<BuildableStructure> structure);
  void setStructureToBuildStage(BuildStage stage);
  // TODO not a contract of EventManager! REFACTOR!
  Shader& getLinesShader();

private:
  void handleMousePressedLeft();
  void handleMousePressedRight();

  glm::mat4& _view;
  glm::mat4& _projection;
  GLFWwindow* _window;
  Camera& _camera;
  Game* _game;
  Shader& _textureShader;
  Shader& _colorShader;
  Shader& _linesShader;
  Tank* _tankSelected{ nullptr };
  VehicleGroup _tanksSelected;
  Tank* _tankUnderAttack{ nullptr };
  Buildable* _structureSelected{ nullptr };
  Buildable* _barrierSelected{ nullptr };
  std::shared_ptr<BuildableStructure> _structureToBuild{ nullptr };
  BuildStage _structureToBuildStage;
  Buildable* _structureUnderAttack{ nullptr };

  Terrain* _terrain;
  RectangleRegion _selection;
  bool _selectionActive{ false };
};

#endif
