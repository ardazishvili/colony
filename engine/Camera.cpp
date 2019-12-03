#include <GLFW/glfw3.h>

#include "Camera.h"

#include <iostream>

Camera::Camera(glm::vec3 positionVector,
	       glm::vec3 lookAtVector,
	       glm::vec3 upVector) :
	_position(positionVector),
	_up(upVector)
{
  float wDiff = ::abs(positionVector.z - lookAtVector.z);
  float yDiff = ::abs(positionVector.y - lookAtVector.y);
  
  _pitch = glm::degrees(::atan(wDiff / yDiff));
  std::cout << "_pitch= " << _pitch << std::endl;

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
  
  _position -= glm::normalize(glm::cross(_front, _up)) * _speed;
}

void Camera::moveRight()
{
  _position += glm::normalize(glm::cross(_front, _up)) * _speed;
}

void Camera::tilt(double x, double y)
{
  if ( _firstMouse ) {
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

  _yaw += xOffset;
  _pitch += yOffset;

  if (_pitch > 89.0f) {
    _pitch = 89.0f;
  }
  if (_pitch < -89.0f) {
    _pitch = -89.0f;
  }

  updateFront();
  std::cout << "_pitch= " << _pitch << std::endl;
}

void Camera::zoom(double factor)
{
  if(_fov >= 1.0f && _fov <= 45.0f)
  	_fov -= factor;
  if(_fov <= 1.0f)
  	_fov = 1.0f;
  if(_fov >= 45.0f)
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
  front.y = ::sin(glm::radians(_pitch));
  front.z = ::cos(glm::radians(_pitch)) * ::sin(glm::radians(_yaw));
  _front = glm::normalize(front);
}

float Camera::getPitch() const
{
  return _pitch;
}
