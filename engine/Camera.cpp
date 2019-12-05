#include <GLFW/glfw3.h>

#include "Camera.h"

#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up) :
  _position(position), _up(up)
{
  float a = ::abs(position.z - lookAt.z);
  auto rCamPosition = ::sqrt(::pow(position.x, 2) + ::pow(position.y, 2));
  auto rLookAt = ::sqrt(::pow(lookAt.x, 2) + ::pow(lookAt.y, 2));
  float b = ::abs(rCamPosition - rLookAt);

  _pitch = -glm::degrees(::atan(a / b));
  _camRadius = b;

  updateFront();
}

void Camera::updateSpeed()
{
  float currentFrame = glfwGetTime();
  _deltaTime = currentFrame - _lastFrame;
  _lastFrame = currentFrame;
  _speed = 5.5f * _deltaTime; // adjust accordingly
}

void Camera::moveForward()
{
  _position += _speed * _front;
}

void Camera::moveBackward()
{
  _position -= _speed * _front;
}

void Camera::moveLeft()
{
  _yaw -= 1.0f;
  updatePosition();
}

void Camera::moveRight()
{
  _yaw += 1.0f;
  updatePosition();
}

void Camera::tilt(double x, double y)
{
  if (_firstMouse) {
    _lastX = x;
    _lastY = y;
    _firstMouse = false;
  }
  float xOffset = x - _lastX;
  float yOffset = _lastY - y;
  _lastX = x;
  _lastY = y;

  float sensitivity = 0.05f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  _yaw -= xOffset;
  _pitch += yOffset;

  if (_pitch > 89.0f) {
    _pitch = 89.0f;
  }
  if (_pitch < -89.0f) {
    _pitch = -89.0f;
  }

  updateFront();
  std::cout << "_pitch= " << _pitch << std::endl;
  std::cout << "_yaw= " << _yaw << std::endl;
}

void Camera::zoom(double factor)
{
  if (_fov >= 1.0f && _fov <= 45.0f)
    _fov -= factor;
  if (_fov <= 1.0f)
    _fov = 1.0f;
  if (_fov >= 45.0f)
    _fov = 45.0f;
}

float Camera::fov() const
{
  return _fov;
}

glm::vec3 Camera::eye() const
{
  return _position;
}

glm::vec3 Camera::reference() const
{
  return _position + _front;
}

glm::vec3 Camera::up() const
{
  return _up;
}

void Camera::updateFront()
{
  glm::vec3 front;
  front.x = ::cos(glm::radians(_pitch)) * ::cos(glm::radians(_yaw));
  front.y = ::cos(glm::radians(_pitch)) * ::sin(glm::radians(_yaw));
  front.z = ::sin(glm::radians(_pitch));
  _front = glm::normalize(front);
}

float Camera::getPitch() const
{
  return _pitch;
}

void Camera::updatePosition()
{
  _position.x = -::sin(glm::radians(_yaw + 90)) * _camRadius;
  _position.y = ::cos(glm::radians(_yaw + 90)) * _camRadius;
  updateFront();
}
