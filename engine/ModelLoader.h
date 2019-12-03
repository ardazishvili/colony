#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <map>
#include <memory>

#include "Model.h"

enum class Models {
  Shell,
  Tank,
  TankFactory,
  Hq
};

enum class MenuTextures {
  Hq,
  TankFactory,
  TankLight,
  TankMedium,
  TankHeavy
};

using ModelsMapping = std::map<Models, std::shared_ptr<Model>>;
using MenuTexturesMapping = std::map<MenuTextures, std::shared_ptr<Texture>>;
class ModelLoader {
public:
  ModelLoader() = default;
  void load();
  ModelsMapping models();
  MenuTexturesMapping menuTextures();

private:
  ModelsMapping _models;
  MenuTexturesMapping _menuTextures;
};

#endif
