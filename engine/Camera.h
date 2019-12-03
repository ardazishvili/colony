#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
  Camera() = delete;
  Camera(glm::vec3 positionVector, glm::vec3 lookAtVector, glm::vec3 upVector);
  void updateSpeed();
  void moveForward();
  void moveBackward();
  void moveLeft();
  void moveRight();
  void tilt(double x, double y);
  void zoom(double factor);
  float fov() const;
  glm::vec3 eye() const;
  glm::vec3 reference() const;
  glm::vec3 up() const;
  float getPitch() const;

private:
  void updateFront();

  glm::vec3 _position;
  glm::vec3 _front;
  glm::vec3 _up;
  float _speed;
  float _deltaTime { 0.0 };
  float _lastFrame { 0.0 };
  float _fov { 45.0f };
  float _yaw { -90.0f };
  float _pitch;
  float _lastX { 400 };
  float _lastY { 300 };
  bool _firstMouse { true };
};

#endif
