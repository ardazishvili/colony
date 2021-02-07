#include "GroundStructure.h"

GroundStructure::GroundStructure(std::unique_ptr<StructureView> view) :
  Buildable(view.get()), Structure<GroundStructure>(view.get()), Selectable<GroundStructure>(view.get()),
  _view(std::move(view))
{
}

void GroundStructure::render()
{
  Structure<GroundStructure>::render();
}
