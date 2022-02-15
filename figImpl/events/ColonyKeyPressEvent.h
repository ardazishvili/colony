#pragma once

#include "fig/events/Event.h"

class ColonyKeyPressEvent : public fig::KeyboardPressEvent {
 public:
  ColonyKeyPressEvent(int key, int scancode, int mods);

  void process(fig::Camera* camera, fig::EventManager* eventManager);
};
