#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "../logic/EventManager.h"
#include "Camera.h"
#include "events/Event.h"

class Window
{
public:
  Window(std::unique_ptr<EventManager>& em,
         Camera& c,
         glm::mat4& view,
         glm::mat4& projection,
         std::function<void(std::unique_ptr<Event> event)> onEvent);
  Window(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&&) = delete;
  ~Window();

  void preUpdate();
  void postUpdate();
  float width() const;
  float height() const;
  void getCursorPos(double* xpos, double* ypos) const;

  GLFWwindow* _window;

private:
  void showDebug();
  void processInput(GLFWwindow* window);

  float _screenWidth;
  float _screenHeight;
  std::unique_ptr<EventManager>& _eventManager;
  Camera& _camera;
  glm::mat4& _view;
  glm::mat4& _projection;

  static std::function<void(std::unique_ptr<Event> event)> _onEvent;
};

#endif
