#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "fig/Core.h"

#include "figImpl/ColonyApplication.h"
#include "figImpl/globals.h"

using json = nlohmann::json;

auto main(int argc, char** argv) -> int
{
  std::filesystem::path config_name = "/home/roman/repos/colony/config.json";
  std::fstream config(config_name, std::ios::in | std::ios::out);
  json j;
  config >> j;
  std::cout << j["window_width"];
  std::filesystem::resize_file(config_name, 0);
  config.seekp(0);
  j["window_height"] = 1923;
  config << j.dump(4);

  try {
    auto app = gApp();
    app->run();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
