#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include "../imgui/imgui.h"
#include "Log.h"

class Logger
{
public:
  void log(const std::string& str, float f);
  void log(const std::string& str);
  void render();

private:
  Log _log;
};

#endif
