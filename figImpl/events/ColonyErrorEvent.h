#ifndef COLONY_ERROR_EVENT_H
#define COLONY_ERROR_EVENT_H

#include "../../fig/events/Event.h"
#include <iostream>

class ErrorEvent : public Event
{
public:
  void process(Camera* camera, EventManager* eventManager) override
  {
    std::cout << "ErrorEvent test output" << std::endl;
  }
};

#endif
