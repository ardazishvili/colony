#pragma once

#include "fig/events/Event.h"

class ColonyMouseScrollEvent : public fig::MouseScrollEvent {
 public:
  ColonyMouseScrollEvent(double xoffset, double yoffset);

  void process(fig::Camera* camera, fig::EventManager* eventManager) override;
};
