#ifndef GROUND_STRUCTURE_H
#define GROUND_STRUCTURE_H

#include "../concepts/Buildable.h"
#include "../concepts/Selectable.h"
#include "Structure.h"

class GroundStructure
  : public Buildable
  , public Structure<GroundStructure>
  , public Selectable<GroundStructure>
{
public:
  GroundStructure(std::unique_ptr<StructureView> view);
  virtual UnitBuilders getUnitBuilders(Game* game) = 0;
  virtual StructureBuilders getStructureBuilders() = 0;
  void render() override;

protected:
  friend Selectable;
  friend Structure;

  std::unique_ptr<StructureView> _view;
};

#endif
