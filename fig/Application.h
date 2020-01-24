#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
public:
  Application() = default;
  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(const Application&) = delete;
  Application& operator=(Application&&) = delete;
  virtual ~Application() = default;

  virtual void run() = 0;
};

#endif
