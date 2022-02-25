#pragma once

#include <memory>

#include "view/AbstractPlantView.h"

class AbstractPlant {
 public:
  AbstractPlant(std::unique_ptr<AbstractPlantView> view);
  virtual void render();
  virtual glm::vec2 position();

  virtual ~AbstractPlant() = default;
  AbstractPlant(const AbstractPlant&) = delete;
  AbstractPlant(AbstractPlant&&) = delete;
  AbstractPlant& operator=(const AbstractPlant&) = delete;
  AbstractPlant& operator=(AbstractPlant&&) = delete;

 protected:
  std::unique_ptr<AbstractPlantView> _view;
};
