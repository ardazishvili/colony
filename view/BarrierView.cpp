#include "../imgui/imgui.h"

#include "../engine/Circle.h"
#include "../globals.h"
#include "BarrierView.h"

float BarrierView::BARRIER_HEALTH_BAR_WIDTH = 1.2f;
float BarrierView::BARRIER_HEALTH_BAR_HEIGHT = 0.15f;

BarrierView::BarrierView(Shader& shader, glm::vec3 position, Terrain* terrain) :
  StructureView(
    shader,
    position,
    1.41 / 2,
    { -0.3, 0, BARRIER_HEALTH_BAR_WIDTH, BARRIER_HEALTH_BAR_HEIGHT },
    TexturePackType::Initial),
  _terrain(terrain)
{
  _model = modelLoader->models()[Models::Barrier];
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");
}

void BarrierView::draw()
{
  /* _terrain->updateLivingArea(_livingArea); */

  static bool bd = false;
  ImGui::Begin("Barriers display");
  ImGui::SetWindowPos(ImVec2(0, 680));
  ImGui::SetWindowSize(ImVec2(200, 40));
  ImGui::Checkbox("state", &bd);
  ImGui::End();
  if (bd) {
    _shader.use();
    _shader.configure();
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _shader.setBool("animated", false);
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    model = glm::scale(model, glm::vec3(_scaleFactor));
    _shader.setTransformation("model", glm::value_ptr(model));
    _model->render();
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    showHealthBar();
  }
}

float BarrierView::radius() const
{
  return _scaleFactor;
}
