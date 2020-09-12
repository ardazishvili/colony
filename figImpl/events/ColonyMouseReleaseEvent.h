#ifndef COLONY_MOUSE_RELEASE_EVENT_H
#define COLONY_MOUSE_RELEASE_EVENT_H

#include "../../fig/events/Event.h"

class ColonyMouseReleaseEvent : public fig::MouseReleaseEvent
{
public:
  ColonyMouseReleaseEvent(int button);

  void process(fig::Camera* camera, fig::EventManager* eventManager) override;

private:
  void handleMouseReleasedMiddle(fig::EventManager* m);
  void handleMouseReleased(fig::EventManager* m);
};

#endif
