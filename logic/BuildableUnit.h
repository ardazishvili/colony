#ifndef BUILDABLE_UNIT_H
#define BUILDABLE_UNIT_H

#include "../engine/Path.h"
#include "../math/AStar.h"
#include "Buildable.h"

class BuildableUnit : public Buildable
{
public:
  BuildableUnit(Shader& textureShader, Shader& linesShader, AStar* router);
  bool isUnderCursor(const glm::vec3& mousePoint) override;
  virtual void render() override;

protected:
  std::shared_ptr<Path> _path;
  AStar* _router;
};

#endif
