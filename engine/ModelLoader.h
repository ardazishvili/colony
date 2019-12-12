#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <map>
#include <memory>

#include "Model.h"

enum class Models { Shell, Tank, TankFactory, Hq, Plant, Barrier };

enum class MenuTextures {
  Hq,
  TankFactory,
  TankLight,
  TankMedium,
  TankHeavy,
  Plant,
  Barrier
};

using ModelsMapping = std::map<Models, std::shared_ptr<Model>>;
using MenuTexturesMapping = std::map<MenuTextures, std::shared_ptr<Texture>>;
class ModelLoader
{
public:
  ModelLoader(Shader& shader);
  void load();
  ModelsMapping models();
  MenuTexturesMapping menuTextures();

private:
  Shader& _shader;
  ModelsMapping _models;
  MenuTexturesMapping _menuTextures;
};

#endif
