#ifndef BUILDABLE_UNIT_H
#define BUILDABLE_UNIT_H

#include "../engine/Path.h"
#include "../view/UnitView.h"
#include "Buildable.h"

class BuildableUnit : public Buildable
{
public:
  BuildableUnit(Shader& textureShader,
                Shader& linesShader,
                std::unique_ptr<UnitView> view);
  bool isUnderCursor(const glm::vec3& mousePoint) override;
  virtual void startShooting(Buildable* other) = 0;
  virtual void startMoving(glm::vec3 endPoint) = 0;
  virtual void render() override;

protected:
  std::unique_ptr<UnitView> _view;
  Path _path;
};

#endif
