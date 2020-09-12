#include "AttackUnitView.h"

AttackUnitView::AttackUnitView(fig::Shader& shader,
                               glm::vec3 position,
                               float selectionRadius,
                               HealthBarParams healthBarParams,
                               fig::TexturePackType texturesType) :
  UnitView(shader, position, selectionRadius, healthBarParams, texturesType)
{
}
