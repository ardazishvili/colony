#ifndef COLONY_APPLICATION_H
#define COLONY_APPLICATION_H

#include "../fig/Application.h"
#include "../fig/events/Event.h"
#include "../fig/events/EventFabric.h"
#include <memory>

template<typename T>
class ColonyApplication : public fig::Application<T>
{
public:
  ColonyApplication();

  void run() override;
  void tick() override{};

private:
  std::function<void(std::unique_ptr<fig::Event> event)> _onEvent;
  std::unique_ptr<fig::EventFabric> _eventFabric;
};

#endif
