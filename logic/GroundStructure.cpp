#include "GroundStructure.h"

GroundStructure::GroundStructure(Shader& textureShader,
                                 Shader& linesShader,
                                 std::unique_ptr<StructureView> view) :
  Buildable(textureShader, linesShader),
  Structure<GroundStructure>(view.get()), Selectable<GroundStructure>(
                                            view.get()),
  _view(std::move(view))
{
  _viewPtr = _view.get();
}

void GroundStructure::render()
{
  Structure<GroundStructure>::render();
}

