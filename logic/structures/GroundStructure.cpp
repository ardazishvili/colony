#include "GroundStructure.h"

GroundStructure::GroundStructure(fig::Shader& textureShader,
                                 fig::Shader& linesShader,
                                 std::unique_ptr<StructureView> view) :
  Buildable(textureShader, linesShader, view.get()),
  Structure<GroundStructure>(view.get()), Selectable<GroundStructure>(
                                            view.get()),
  _view(std::move(view))
{
}

void GroundStructure::render()
{
  Structure<GroundStructure>::render();
}

