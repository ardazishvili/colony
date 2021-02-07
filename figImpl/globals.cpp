#include <filesystem>

#include "../fig/globals.h"

#include "ColonyApplication.h"
#include "globals.h"

fig::Application<SpdBackend>* gApp()
{
  static auto app = std::make_unique<ColonyApplication<SpdBackend>>();
  return app.get();
}
bool flatView = true;
Config CONFIG = Config(std::filesystem::current_path().string() + "/config.json");
std::unordered_map<ShaderType, std::unique_ptr<fig::Shader>> SHADERS_MAP;
