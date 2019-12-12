#include "../imgui/imgui.h"

#include "../engine/Circle.h"
#include "../globals.h"
#include "BarrierView.h"

float BarrierView::BARRIER_HEALTH_BAR_WIDTH = 1.2f;
float BarrierView::BARRIER_HEALTH_BAR_HEIGHT = 0.15f;

BarrierView::BarrierView(Shader& shader, glm::vec3 position, Terrain* terrain) :
  View(shader, position), _healthBar(shader,
                                     position.x - 0.3,
                                     position.y,
                                     _position.x + BARRIER_HEALTH_BAR_WIDTH,
                                     _position.y + BARRIER_HEALTH_BAR_HEIGHT,
                                     1),
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
glm::vec3 BarrierView::position() const
{
  return _position;
  /* return glm::vec2(_position.x, _position.y); */
}

void BarrierView::setTexture(Status status)
{
}

bool BarrierView::contain(glm::vec3 point) const
{
  const auto radius = 1.41f / 2;
  const auto distance =
    ::sqrt(::pow(_position.x - point.x, 2) + ::pow(_position.y - point.y, 2));

  return distance < radius;
}

void BarrierView::setHealthBarScaleFactor(float factor)
{
  _healthBarScaleFactor = factor;
}

void BarrierView::showHealthBar()
{
  _healthBar.setScaleX(_healthBarScaleFactor);
  _healthBar.render();
}

float BarrierView::radius() const
{
  return _scaleFactor;
}
