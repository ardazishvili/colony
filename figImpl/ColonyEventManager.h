#ifndef COLONY_EVENT_MANAGER_H
#define COLONY_EVENT_MANAGER_H

#include <GLFW/glfw3.h>

#include "../fig/Camera.h"
#include "../fig/EventManager.h"
#include "../fig/HeightsSegment.h"
#include "../fig/ObstaclesSegment.h"
#include "../fig/RectangleShape.h"
#include "../fig/events/Event.h"
#include "../fig/math/AStar.h"

#include "../logic/Game.h"
#include "../logic/Tank.h"

class ColonyWindow;
class ColonyEventManager : public EventManager
{
public:
  ColonyEventManager(glm::mat4& view,
                     glm::mat4& projection,
                     ColonyWindow* window,
                     Game* game,
                     Camera& camera,
                     Shader& textureShader,
                     Shader& colorShader,
                     Shader& colorNonFlatShader,
                     Shader& linesShader,
                     Terrain* terrain,
                     std::shared_ptr<ObstaclesSegment> mo,
                     AStar* astar);
  void tick();
  /* static glm::vec3 unProject(ColonyWindow* window, */
  /*                            glm::mat4& view, */
  /*                            glm::mat4& proj); */
  void setStructureToBuild(std::shared_ptr<GroundStructure> structure);
  void setStructureToBuildStage(BuildStage stage);

private:
  glm::mat4& _view;
  glm::mat4& _projection;
  /* ColonyWindow* _window; */
  Window* _window;
  Camera& _camera;
  Game* _game;
  Shader& _textureShader;
  Shader& _colorShader;
  Shader& _colorNonFlatShader;
  Shader& _linesShader;
  AttackUnit* _tankSelected{ nullptr };
  VehicleGroup _tanksSelected;
  AttackUnit* _tankUnderAttack{ nullptr };
  Buildable* _structureSelected{ nullptr };
  Buildable* _barrierSelected{ nullptr };
  std::shared_ptr<GroundStructure> _structureToBuild{ nullptr };
  BuildStage _structureToBuildStage;
  Buildable* _structureUnderAttack{ nullptr };

  Terrain* _terrain;
  RectangleShape _selection;
  bool _selectionActive{ false };

  std::shared_ptr<HeightsSegment> _heightsSegment;
  std::shared_ptr<ObstaclesSegment> _obstaclesSegment;
  std::shared_ptr<ObstaclesSegment> _mapObstacles;
  AStar* _astar;

  friend class ColonyKeyPressEvent;
  friend class ColonyKeyReleaseEvent;
  friend class ColonyKeyRepeatEvent;
  friend class ColonyMousePressedEvent;
  friend class ColonyMouseReleaseEvent;
  friend class ColonyMouseMoveEvent;
};

#endif
