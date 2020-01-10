#ifndef STRUCTURE_VIEW_H
#define STRUCTURE_VIEW_H

#include "SelectableView.h"

class StructureView : public SelectableView
{
public:
  StructureView(Shader& shader,
                glm::vec3 position,
                float selectionRadius,
                HealthBarParams healthBarParams,
                TexturePackType texturesType);

  void rotate(float degreeAngle);
  void move(glm::vec3 position);

protected:
  void showHealthBar() override;
};

#endif
