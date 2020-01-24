#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "../fig/Camera.h"
#include "../fig/events/Event.h"
#include "../logic/EventManager.h"

class EventFabric;
class Window
{
public:
  Window(glm::mat4& view,
         glm::mat4& projection,
         std::function<void(std::unique_ptr<Event> event)> onEvent,
         EventFabric* eventFabric);
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

  float _screenWidth;
  float _screenHeight;
  glm::mat4& _view;
  glm::mat4& _projection;

  static EventFabric* _eventFabric;
  static std::function<void(std::unique_ptr<Event> event)> _onEvent;
};

#endif
