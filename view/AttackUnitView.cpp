#include "view/AttackUnitView.h"

AttackUnitView::AttackUnitView(glm::vec3 position, float selectionRadius,
                               HealthBarParams healthBarParams,
                               fig::TexturePackType texturesType)
    : UnitView(position, selectionRadius, healthBarParams, texturesType) {}
