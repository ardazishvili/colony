#ifndef COLONY_MOUSE_RELEASE_EVENT_H
#define COLONY_MOUSE_RELEASE_EVENT_H

#include "Event.h"

class ColonyMouseReleaseEvent : public MouseReleaseEvent
{
public:
  ColonyMouseReleaseEvent(int button);

  void process(Camera* camera, EventManager* eventManager) override;

private:
  void handleMouseReleasedMiddle(EventManager* m);
  void handleMouseReleased(EventManager* m);
};

#endif
