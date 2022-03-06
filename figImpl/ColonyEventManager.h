#pragma once

#include <memory>

#include "fig/Camera.h"
#include "fig/EventManager.h"
#include "fig/HeightsSegment.h"
#include "fig/ObstaclesSegment.h"
#include "fig/RectangleShape.h"
#include "fig/events/Event.h"
#include "fig/math/AStar.h"
#include "logic/Game.h"
#include "logic/units/Tank.h"

class ColonyWindow;
class ColonyEventManager : public fig::EventManager {
 public:
  ColonyEventManager(glm::mat4& view, glm::mat4& projection,
                     fig::Window& window, Game& game, fig::Camera& camera,
                     fig::Terrain& terrain,
                     std::unique_ptr<fig::ObstaclesSegment> mapObstacles,
                     fig::AStar& astar);
  void tick();
  void setStructureToBuild(GroundStructure* structure);
  void setStructureToBuildStage(BuildStage stage);

  void clearHeightSegment() { _heightsSegment.reset(); }
  void setHeightSegment(std::unique_ptr<fig::HeightsSegment> segment) {
    _heightsSegment = std::move(segment);
  }

  void clearObstaclesSegment() { _obstaclesSegment.reset(); }
  void setObstaclesSegment(std::unique_ptr<fig::ObstaclesSegment> segment) {
    _obstaclesSegment = std::move(segment);
  }

 private:
  glm::mat4& _view;
  glm::mat4& _projection;
  fig::Window& _window;
  fig::Camera& _camera;
  Game& _game;
  AttackUnit* _tankSelected{nullptr};
  VehicleGroup _tanksSelected;
  AttackUnit* _tankUnderAttack{nullptr};
  Buildable* _structureSelected{nullptr};
  Buildable* _barrierSelected{nullptr};
  GroundStructure* _structureToBuild{nullptr};
  BuildStage _structureToBuildStage;
  Buildable* _structureUnderAttack{nullptr};

  fig::Terrain& _terrain;
  fig::RectangleShape _selection;
  bool _selectionActive{false};

  std::unique_ptr<fig::HeightsSegment> _heightsSegment;
  std::unique_ptr<fig::ObstaclesSegment> _obstaclesSegment;
  std::unique_ptr<fig::ObstaclesSegment> _mapObstacles;
  fig::AStar& _astar;

  friend class ColonyKeyPressEvent;
  friend class ColonyKeyReleaseEvent;
  friend class ColonyKeyRepeatEvent;
  friend class ColonyMousePressedEvent;
  friend class ColonyMouseReleaseEvent;
  friend class ColonyMouseMoveEvent;
};
