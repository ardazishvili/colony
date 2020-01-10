#ifndef BUILDABLE_NON_ATTACK_UNIT_H
#define BUILDABLE_NON_ATTACK_UNIT_H

#include "../view/UnitView.h"
#include "BuildableUnit.h"

class BuildableNonAttackUnit : public BuildableUnit
{
public:
  BuildableNonAttackUnit(Shader& textureShader,
                         Shader& linesShader,
                         std::unique_ptr<UnitView> view,
                         AStar* router);

protected:
  std::unique_ptr<UnitView> _view;
};

#endif
