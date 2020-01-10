#ifndef GROUND_STRUCTURE_H
#define GROUND_STRUCTURE_H

#include "Buildable.h"
#include "Selectable.h"
#include "Structure.h"

class GroundStructure
  : public Buildable
  , public Structure<GroundStructure>
  , public Selectable<GroundStructure>
{
public:
  GroundStructure(Shader& textureShader,
                  Shader& linesShader,
                  std::unique_ptr<StructureView> view);
  void render() override;

protected:
  friend Selectable;
  friend Structure;

  std::unique_ptr<StructureView> _view;
};

#endif
