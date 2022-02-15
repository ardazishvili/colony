#include "fig/globals.h"

#include <filesystem>

#include "figImpl/ColonyApplication.h"
#include "figImpl/globals.h"

fig::Application<SpdBackend>* gApp() {
  static auto app = std::make_unique<ColonyApplication<SpdBackend>>();
  return app.get();
}
bool flatView = true;
Config CONFIG =
    Config(std::filesystem::current_path().string() + "/config.json");
std::unordered_map<ShaderType, std::unique_ptr<fig::Shader>> SHADERS_MAP;
