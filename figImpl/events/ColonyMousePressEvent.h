#pragma once

#include "fig/events/Event.h"

class ColonyMousePressedEvent : public fig::MousePressEvent {
 public:
  ColonyMousePressedEvent(int button);

  void process(fig::Camera* camera, fig::EventManager* eventManager) override;

 private:
  void handleMousePressedLeft(fig::EventManager* m);
  void handleMousePressedRight(fig::EventManager* m);
  void handleMousePressedMiddle(fig::EventManager* m);
};
