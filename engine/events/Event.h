#ifndef EVENT_H
#define EVENT_H

class EventManager;
class Camera;
class Event
{
public:
  Event() = default;
  Event(const Event&) = delete;
  Event(Event&&) = delete;
  Event& operator=(const Event&) = delete;
  Event& operator=(Event&&) = delete;
  ~Event() = default;

  virtual void process(Camera* camera, EventManager* eventManager) = 0;
};

class KeyboardEvent : public Event
{
};

class KeyboardPressEvent : public KeyboardEvent
{
};

class KeyboardReleaseEvent : public KeyboardEvent
{
};

class KeyboardRepeatEvent : public KeyboardEvent
{
};

class MouseEvent : public Event
{
};

class MousePressEvent : public MouseEvent
{
};

class MouseReleaseEvent : public MouseEvent
{
};

class MouseMoveEvent : public MouseEvent
{
};

#endif
