#ifndef PLANT_VIEW_H
#define PLANT_VIEW_H

#include "AbstractPlantView.h"

class PlantView : public AbstractPlantView
{
public:
  PlantView(glm::vec3 position);
  void draw() override;
};

#endif
