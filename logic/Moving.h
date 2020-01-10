#ifndef MOVING_H
#define MOVING_H

#include "../engine/Path.h"
#include "../engine/Terrain.h"
#include "../view/UnitView.h"

template<typename T>
class Moving
{
public:
  Moving(Shader& linesShader, UnitView* view, float speed);

  void move();
  bool isMoving();
  void setRoute(glm::vec3 endPoint);
  void setTerrain(Terrain* terrain);

protected:
  void startMoving(glm::vec2 endPoint);
  void stopMoving();
  float getMouseAngle(int mouseX, int mouseY);

  UnitView* _view;
  Shader& _linesShader;
  float _speed;
  glm::vec2 _moveIncrement{ 0, 0 };
  glm::vec2 _destination;
  Terrain* _terrain;
  APath _movingRoute;
  static const float MOVE_STOP_TOL;
};

#endif