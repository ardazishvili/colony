#pragma once

#include "logic/concepts/Buildable.h"
#include "logic/concepts/Selectable.h"
#include "logic/structures/Structure.h"

class GroundStructure : public Buildable,
                        public Structure<GroundStructure>,
                        public Selectable<GroundStructure> {
 public:
  GroundStructure(std::unique_ptr<StructureView> view);
  virtual UnitBuilders getUnitBuilders() = 0;
  virtual StructureBuilders getStructureBuilders() = 0;
  void render() override;

 protected:
  friend Selectable;
  friend Structure;

  std::unique_ptr<StructureView> _view;
};
