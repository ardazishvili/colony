#pragma once

#include "fig/events/Event.h"

class ColonyKeyRepeatEvent : public fig::KeyboardRepeatEvent {
 public:
  ColonyKeyRepeatEvent(int key, int scancode, int mods);
  void process(fig::Camera* camera, fig::EventManager* eventManager);
};
