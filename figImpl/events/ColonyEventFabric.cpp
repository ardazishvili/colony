#include "../../fig/events/ErrorEvent.h"

#include "ColonyEventFabric.h"
#include "ColonyKeyPressEvent.h"
#include "ColonyKeyReleaseEvent.h"
#include "ColonyKeyRepeatEvent.h"
#include "ColonyMouseMoveEvent.h"
#include "ColonyMousePressEvent.h"
#include "ColonyMouseReleaseEvent.h"
#include "ColonyMouseScrollEvent.h"

std::unique_ptr<Event> ColonyEventFabric::getKeyPressEvent(GLFWwindow* window,
                                                           int key,
                                                           int scancode,
                                                           int mods)
{
  return std::make_unique<ColonyKeyPressEvent>(window, key, scancode, mods);
}

std::unique_ptr<Event> ColonyEventFabric::getKeyReleaseEvent(GLFWwindow* window,
                                                             int key,
                                                             int scancode,
                                                             int mods)
{
  return std::make_unique<ColonyKeyReleaseEvent>(window, key, scancode, mods);
}

std::unique_ptr<Event> ColonyEventFabric::getKeyRepeatEvent(GLFWwindow* window,
                                                            int key,
                                                            int scancode,
                                                            int mods)
{
  return std::make_unique<ColonyKeyRepeatEvent>(window, key, scancode, mods);
}

std::unique_ptr<Event> ColonyEventFabric::getMouseScrollEvent(
  GLFWwindow* window,
  double xoffset,
  double yoffset)
{
  return std::make_unique<ColonyMouseScrollEvent>(window, xoffset, yoffset);
}

std::unique_ptr<Event> ColonyEventFabric::getMouseMoveEvent(GLFWwindow* window,
                                                            double xpos,
                                                            double ypos)
{
  return std::make_unique<ColonyMouseMoveEvent>(window, xpos, ypos);
}

std::unique_ptr<Event> ColonyEventFabric::getMousePressedEvent(
  GLFWwindow* window,
  int button,
  int action,
  int mods)
{
  return std::make_unique<ColonyMousePressedEvent>(button);
}

std::unique_ptr<Event> ColonyEventFabric::getMouseReleasedEvent(
  GLFWwindow* window,
  int button,
  int action,
  int mods)
{
  return std::make_unique<ColonyMouseReleaseEvent>(button);
}
