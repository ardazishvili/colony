#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
  Window() = default;
  Window(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&&) = delete;
  virtual ~Window() = default;
};

#endif
