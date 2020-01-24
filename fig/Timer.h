#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
  Timer();
  std::chrono::milliseconds elapsed();
  void reload();

private:
  std::chrono::time_point<std::chrono::system_clock> _start { std::chrono::system_clock::now() };
};

#endif
