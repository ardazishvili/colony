#ifndef STRUCTURE_VIEW_H
#define STRUCTURE_VIEW_H

#include "SelectableView.h"

class StructureView : public SelectableView
{
public:
  float angle() const;
  void rotate(float degreeAngle);
  void move(glm::vec3 position);

protected:
  StructureView(Shader& shader,
                glm::vec3 position,
                float selectionRadius,
                HealthBarParams healthBarParams,
                TexturePackType texturesType);
  void showHealthBar() override;

  float _angle{ 0.0f };
};

#endif
