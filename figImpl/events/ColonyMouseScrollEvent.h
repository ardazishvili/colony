#ifndef COLONY_MOUSE_SCROLL_EVENT_H
#define COLONY_MOUSE_SCROLL_EVENT_H

#include "../../fig/events/Event.h"

class ColonyMouseScrollEvent : public MouseScrollEvent
{
public:
  ColonyMouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset);

  void process(Camera* camera, EventManager* eventManager) override;
};

#endif
