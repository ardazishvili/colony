#pragma once

#include "Config.h"
#include "Core.h"

class SettingsGui {
 public:
  SettingsGui(int windowWidth, int windowHeight);
  void show();
  void toggle();

 private:
  bool _visible = false;
  int _width = 600;
  int _height = 400;
  int _windowWidth;
  int _windowHeight;
};
