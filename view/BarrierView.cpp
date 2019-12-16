#include "../imgui/imgui.h"

#include "../engine/Circle.h"
#include "../globals.h"
#include "BarrierView.h"

float BarrierView::BARRIER_HEALTH_BAR_WIDTH = 1.2f;
float BarrierView::BARRIER_HEALTH_BAR_HEIGHT = 0.15f;
const float BarrierView::SHROUD_UP_SPEED = 0.1;
const float BarrierView::SHROUD_HEIGHT = 8.0;

BarrierView::BarrierView(Shader& textureShader,
                         Shader& linesShader,
                         glm::vec3 p,
                         Terrain* terrain) :
  StructureView(
    textureShader,
    p,
    1.41 / 2,
    { -0.3, 0, BARRIER_HEALTH_BAR_WIDTH, BARRIER_HEALTH_BAR_HEIGHT },
    TexturePackType::Initial),
  _terrain(terrain), _beam(linesShader,
                           glm::vec3(p.x, p.y, SHROUD_HEIGHT),
                           glm::vec3(p.x, p.y, p.z + _scaleFactor),
                           0.4f,
                           10),
  _linesShader(linesShader)
{
  _model = modelLoader->models()[Models::Barrier];
  _model->setActiveTexturesPack(TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");

  _shroudModel = modelLoader->models()[Models::Shroud];
  _shroudModel->setActiveTexturesPack(TexturePackType::Initial);
}

void BarrierView::draw()
{
  static bool bd = true;
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
    model =
      glm::rotate(model, glm::radians(_angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(_scaleFactor));
    _shader.setTransformation("model", glm::value_ptr(model));
    _model->setActiveTexturesPack(_texturesType);
    _model->render();
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);

    showHealthBar();
  }
}

void BarrierView::drawShroud()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  auto p = _position;
  _shroudZ = ::min(SHROUD_HEIGHT, _shroudZ + SHROUD_UP_SPEED);
  model = glm::translate(model, glm::vec3(p.x, p.y, _shroudZ));
  _shader.setTransformation("model", glm::value_ptr(model));
  _shroudModel->render();
}

void BarrierView::drawBeam()
{
  _beam.render();
}

float BarrierView::radius() const
{
  return _scaleFactor;
}

bool BarrierView::shroudSetUp() const
{
  return (_shroudZ == SHROUD_HEIGHT);
}

glm::vec3 BarrierView::shroudPosition() const
{
  return glm::vec3(_position.x, _position.y, _position.z + SHROUD_HEIGHT);
}
