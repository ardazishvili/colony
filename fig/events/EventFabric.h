#ifndef EVENT_FABRIC_H
#define EVENT_FABRIC_H

#include <memory>

#include "Event.h"

class EventFabric
{
public:
  virtual std::unique_ptr<Event> getKeyPressEvent(GLFWwindow* window,
                                                  int key,
                                                  int scancode,
                                                  int mods) = 0;
  virtual std::unique_ptr<Event> getKeyReleaseEvent(GLFWwindow* window,
                                                    int key,
                                                    int scancode,
                                                    int mods) = 0;
  virtual std::unique_ptr<Event> getKeyRepeatEvent(GLFWwindow* window,
                                                   int key,
                                                   int scancode,
                                                   int mods) = 0;
  virtual std::unique_ptr<Event> getMouseScrollEvent(GLFWwindow* window,
                                                     double xoffset,
                                                     double yoffset) = 0;
  virtual std::unique_ptr<Event> getMouseMoveEvent(GLFWwindow* window,
                                                   double xpos,
                                                   double ypos) = 0;
  virtual std::unique_ptr<Event> getMousePressedEvent(GLFWwindow* window,
                                                      int button,
                                                      int action,
                                                      int mods) = 0;
  virtual std::unique_ptr<Event> getMouseReleasedEvent(GLFWwindow* window,
                                                       int button,
                                                       int action,
                                                       int mods) = 0;
};

#endif
