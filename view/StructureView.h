#ifndef STRUCTURE_VIEW_H
#define STRUCTURE_VIEW_H

#include "SelectableView.h"

class StructureView : public SelectableView
{
public:
  StructureView(fig::Shader& shader,
                glm::vec3 position,
                float selectionRadius,
                HealthBarParams healthBarParams,
                fig::TexturePackType texturesType);

  void rotate(float degreeAngle);
  void move(glm::vec3 position);

protected:
  void showHealthBar() override;
};

#endif
