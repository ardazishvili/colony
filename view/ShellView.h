#pragma

#include "fig/Model.h"
#include "view/View.h"

class ShellView : public View {
 public:
  ShellView(glm::vec3 position);
  void draw() override;
  void move(glm::vec2 moveIncrement);
};
