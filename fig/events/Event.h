#ifndef EVENT_H
#define EVENT_H

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

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
public:
  KeyboardEvent(GLFWwindow* window, int key, int scancode, int mods) :
    _window(window), _key(key), _scancode(), _mods(mods)
  {
  }

protected:
  GLFWwindow* _window;
  int _key;
  int _scancode;
  int _mods;
};

class KeyboardPressEvent : public KeyboardEvent
{
public:
  KeyboardPressEvent(GLFWwindow* window, int key, int scancode, int mods) :
    KeyboardEvent(window, key, scancode, mods)
  {
  }
};

class KeyboardReleaseEvent : public KeyboardEvent
{
public:
  KeyboardReleaseEvent(GLFWwindow* window, int key, int scancode, int mods) :
    KeyboardEvent(window, key, scancode, mods)
  {
  }
};

class KeyboardRepeatEvent : public KeyboardEvent
{
public:
  KeyboardRepeatEvent(GLFWwindow* window, int key, int scancode, int mods) :
    KeyboardEvent(window, key, scancode, mods)
  {
  }
};

class MouseEvent : public Event
{
};

class MouseButtonEvent : public MouseEvent
{
public:
  MouseButtonEvent(int button) : _button(button)
  {
  }

protected:
  int _button;
};

class MousePressEvent : public MouseButtonEvent
{
public:
  MousePressEvent(int button) : MouseButtonEvent(button)
  {
  }
};

class MouseReleaseEvent : public MouseButtonEvent
{
public:
  MouseReleaseEvent(int button) : MouseButtonEvent(button)
  {
  }
};

class MouseMoveEvent : public MouseEvent
{
public:
  MouseMoveEvent(GLFWwindow* window, double xpos, double ypos) :
    _window(window), _xpos(xpos), _ypos(ypos)
  {
  }

protected:
  GLFWwindow* _window;
  double _xpos;
  double _ypos;
};

class MouseScrollEvent : public MouseEvent
{
public:
  MouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset) :
    _window(window), _xoffset(xoffset), _yoffset(yoffset)
  {
  }

protected:
  GLFWwindow* _window;
  double _xoffset;
  double _yoffset;
};

#endif
