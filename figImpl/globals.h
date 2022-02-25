#include <memory>
#include <unordered_map>

#include "fig/Application.h"
#include "fig/Config.h"
#include "fig/SpdBackend.h"

enum class ShaderType { TEXTURE, COLOR, COLOR_NON_FLAT, LAMP, LINES, SKYBOX };

extern std::unordered_map<ShaderType, std::unique_ptr<fig::Shader>> SHADERS_MAP;

fig::Application<SpdBackend>* gApp();
extern bool flatView;
extern Config CONFIG;
