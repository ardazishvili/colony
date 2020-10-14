#include "globals.h"
#include "../fig/globals.h"
#include "ColonyApplication.h"
#include <filesystem>

fig::Application<SpdBackend>* gApp()
{
  static auto app = std::make_unique<ColonyApplication<SpdBackend>>();
  return app.get();
}
bool flatView = true;
Config CONFIG =
  Config(std::filesystem::current_path().string() + "/config.json");
