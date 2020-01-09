#ifndef ABSTRACT_PLANT_VIEW_H
#define ABSTRACT_PLANT_VIEW_H

#include "View.h"

class AbstractPlantView : public View
{
public:
  AbstractPlantView(Shader& shader, glm::vec3 position);
  virtual void draw();
};

#endif
