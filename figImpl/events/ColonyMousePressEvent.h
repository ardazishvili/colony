#ifndef COLONY_MOUSE_PRESS_EVENT_H
#define COLONY_MOUSE_PRESS_EVENT_H

#include "../../fig/events/Event.h"

class ColonyMousePressedEvent : public MousePressEvent
{
public:
  ColonyMousePressedEvent(int button);

  void process(Camera* camera, EventManager* eventManager) override;

private:
  void handleMousePressedLeft(EventManager* m);
  void handleMousePressedRight(EventManager* m);
  void handleMousePressedMiddle(EventManager* m);
};

#endif
