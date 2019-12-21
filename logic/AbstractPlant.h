#ifndef ABSTRACT_PLANT_H
#define ABSTRACT_PLANT_H

#include <memory>

#include "../view/AbstractPlantView.h"

class AbstractPlant
{
public:
  AbstractPlant(std::unique_ptr<AbstractPlantView> view);
  virtual void render();
  virtual glm::vec2 position();

protected:
  std::unique_ptr<AbstractPlantView> _view;
};

using Plants = std::vector<std::shared_ptr<AbstractPlant>>;

#endif
