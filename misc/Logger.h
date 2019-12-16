#ifndef LOGGER_H
#define LOGGER_H

#include "../imgui/imgui.h"
#include "Log.h"

class Logger
{
public:
  void log();

private:
  Log _log;
};

#endif
