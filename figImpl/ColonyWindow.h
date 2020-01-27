#ifndef COLONY_WINDOW_H
#define COLONY_WINDOW_H

#include <functional>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "../fig/Camera.h"
#include "../fig/Window.h"
#include "../fig/events/Event.h"

class EventFabric;
class ColonyWindow : public Window
{
public:
  ColonyWindow(glm::mat4& view,
               glm::mat4& projection,
               EventFabric* eventFabric,
               const Window::Param& param);
  ~ColonyWindow() override;
  void setOnEvent(std::function<void(std::unique_ptr<Event> event)> onEvent);

  void update();
  void show();
  float width() const override;
  float height() const override;
  void getCursorPos(double* xpos, double* ypos) const;

private:
  glm::mat4& _view;
  glm::mat4& _projection;

  static EventFabric* _eventFabric;
  static std::function<void(std::unique_ptr<Event> event)> _onEvent;
};

#endif
