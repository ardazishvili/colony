#include "AttackUnitView.h"

AttackUnitView::AttackUnitView(Shader& shader,
                               glm::vec3 position,
                               float selectionRadius,
                               HealthBarParams healthBarParams,
                               TexturePackType texturesType) :
  UnitView(shader, position, selectionRadius, healthBarParams, texturesType)
{
}
