#ifndef LOG_H
#define LOG_H

#include "../imgui/imgui.h"

struct Log
{
  ImGuiTextBuffer Buf;
  ImGuiTextFilter Filter;
  ImVector<int> LineOffsets;
  bool AutoScroll;

  Log();
  void Clear();
  void AddLog(const char* fmt, ...);
  void Draw(const char* title, bool* p_open = NULL);
};
#endif
