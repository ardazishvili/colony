#pragma once

#include "EventManager.h"
#include "fig/events/Event.h"

class ColonyKeyReleaseEvent : public fig::KeyboardReleaseEvent {
 public:
  ColonyKeyReleaseEvent(int key, int scancode, int mods);
  void buildTankFactory(fig::EventManager* manager);
  void createTank(fig::EventManager* manager);
  void buildHq(fig::EventManager* manager);
  void buildBarrier(fig::EventManager* manager);
  void buildTurbine(fig::EventManager* manager);
  void processLEFT_SHIFT(fig::EventManager* manager);
  void closeWindow(fig::EventManager* manager);
};
