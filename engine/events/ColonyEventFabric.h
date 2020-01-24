#ifndef COLONY_EVENT_FABRIC_H
#define COLONY_EVENT_FABRIC_H

#include "EventFabric.h"

class ColonyEventFabric : public EventFabric
{
public:
  std::unique_ptr<Event> getKeyPressEvent(GLFWwindow* window,
                                          int key,
                                          int scancode,
                                          int mods) override;
  std::unique_ptr<Event> getKeyReleaseEvent(GLFWwindow* window,
                                            int key,
                                            int scancode,
                                            int mods) override;
  std::unique_ptr<Event> getKeyRepeatEvent(GLFWwindow* window,
                                           int key,
                                           int scancode,
                                           int mods) override;
  std::unique_ptr<Event> getMouseScrollEvent(GLFWwindow* window,
                                             double xoffset,
                                             double yoffset) override;
  std::unique_ptr<Event> getMouseMoveEvent(GLFWwindow* window,
                                           double xpos,
                                           double ypos) override;
  std::unique_ptr<Event> getMousePressedEvent(GLFWwindow* window,
                                              int button,
                                              int action,
                                              int mods) override;
  std::unique_ptr<Event> getMouseReleasedEvent(GLFWwindow* window,
                                               int button,
                                               int action,
                                               int mods) override;
};

#endif
