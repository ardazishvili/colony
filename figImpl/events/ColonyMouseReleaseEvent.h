#pragma once

#include "fig/events/Event.h"

class ColonyMouseReleaseEvent : public fig::MouseReleaseEvent {
 public:
  ColonyMouseReleaseEvent(int button);

  void process(fig::Camera* camera, fig::EventManager* eventManager) override;

 private:
  void handleMouseReleasedMiddle(fig::EventManager* m);
  void handleMouseReleased(fig::EventManager* m);
};
