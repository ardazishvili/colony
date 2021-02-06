#ifndef COLONY_EVENT_FABRIC_H
#define COLONY_EVENT_FABRIC_H

#include "../../fig/events/EventFabric.h"

class ColonyEventFabric : public fig::EventFabric
{
public:
  std::unique_ptr<fig::Event> getKeyPressEvent(int key, int scancode, int mods) override;
  std::unique_ptr<fig::Event> getKeyReleaseEvent(int key, int scancode, int mods) override;
  std::unique_ptr<fig::Event> getKeyRepeatEvent(int key, int scancode, int mods) override;
  std::unique_ptr<fig::Event> getMouseScrollEvent(double xoffset, double yoffset) override;
  std::unique_ptr<fig::Event> getMouseMoveEvent(double xpos, double ypos) override;
  std::unique_ptr<fig::Event> getMousePressedEvent(int button, int action, int mods) override;
  std::unique_ptr<fig::Event> getMouseReleasedEvent(int button, int action, int mods) override;
};

#endif
