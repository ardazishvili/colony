#include "../../fig/events/ErrorEvent.h"

#include "ColonyEventFabric.h"
#include "ColonyKeyPressEvent.h"
#include "ColonyKeyReleaseEvent.h"
#include "ColonyKeyRepeatEvent.h"
#include "ColonyMouseMoveEvent.h"
#include "ColonyMousePressEvent.h"
#include "ColonyMouseReleaseEvent.h"
#include "ColonyMouseScrollEvent.h"

std::unique_ptr<fig::Event> ColonyEventFabric::getKeyPressEvent(int key, int scancode, int mods)
{
  return std::make_unique<ColonyKeyPressEvent>(key, scancode, mods);
}

std::unique_ptr<fig::Event> ColonyEventFabric::getKeyReleaseEvent(int key, int scancode, int mods)
{
  return std::make_unique<ColonyKeyReleaseEvent>(key, scancode, mods);
}

std::unique_ptr<fig::Event> ColonyEventFabric::getKeyRepeatEvent(int key, int scancode, int mods)
{
  return std::make_unique<ColonyKeyRepeatEvent>(key, scancode, mods);
}

std::unique_ptr<fig::Event> ColonyEventFabric::getMouseScrollEvent(double xoffset, double yoffset)
{
  return std::make_unique<ColonyMouseScrollEvent>(xoffset, yoffset);
}

std::unique_ptr<fig::Event> ColonyEventFabric::getMouseMoveEvent(double xpos, double ypos)
{
  return std::make_unique<ColonyMouseMoveEvent>(xpos, ypos);
}

std::unique_ptr<fig::Event> ColonyEventFabric::getMousePressedEvent(int button, int action, int mods)
{
  return std::make_unique<ColonyMousePressedEvent>(button);
}

std::unique_ptr<fig::Event> ColonyEventFabric::getMouseReleasedEvent(int button, int action, int mods)
{
  return std::make_unique<ColonyMouseReleaseEvent>(button);
}
