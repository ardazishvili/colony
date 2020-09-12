#ifndef COLONY_MOUSE_MOVE_EVENT_H
#define COLONY_MOUSE_MOVE_EVENT_H

#include "../../fig/events/Event.h"

class ColonyMouseMoveEvent : public fig::MouseMoveEvent
{
public:
  ColonyMouseMoveEvent(double xpos, double ypos);

  void process(fig::Camera* camera, fig::EventManager* eventManager) override;
};

#endif
