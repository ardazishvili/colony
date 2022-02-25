#pragma once

#include "helpers/crtp_helper.h"
#include "logic/concepts/Buildable.h"
#include "logic/concepts/Selectable.h"
#include "view/StructureView.h"

enum class BuildStage { SetPosition, SetAngle, Done };

template <typename T>
class Structure : public crtp<T, Structure> {
 public:
  Structure(StructureView* view);
  Structure(const Structure&) = delete;
  Structure(Structure&&) = delete;
  Structure& operator=(const Structure&) = delete;
  Structure& operator=(Structure&&) = delete;

  virtual ~Structure() = default;

  virtual void commit();
  void setAngle(float angle);
  void setPosition(glm::vec3 position);
  void render();

 protected:
  BuildStage _stage{BuildStage::SetPosition};
  StructureView* _view;

 private:
  Structure() = default;
  friend T;
};
