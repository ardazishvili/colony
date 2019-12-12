#ifndef PLANT_VIEW_H
#define PLANT_VIEW_H

#include "../engine/Model.h"
#include "../engine/Shader.h"
#include "View.h"

class PlantView : public View
{
public:
  PlantView(Shader& shader, glm::vec3 position);
  void draw() override;

private:
  float _scaleFactor{ 1.0f };
};

#endif
