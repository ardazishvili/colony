#ifndef COLONY_MOUSE_MOVE_EVENT_H
#define COLONY_MOUSE_MOVE_EVENT_H

#include "../../fig/events/Event.h"

class ColonyMouseMoveEvent : public MouseMoveEvent
{
public:
  ColonyMouseMoveEvent(double xpos, double ypos);

  void process(Camera* camera, EventManager* eventManager) override;
};

#endif
