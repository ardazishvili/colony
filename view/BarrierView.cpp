#include "../imgui/imgui.h"

#include "../engine/Circle.h"
#include "../globals.h"
#include "BarrierView.h"

float BarrierView::BARRIER_HEALTH_BAR_WIDTH = 1.2f;
float BarrierView::BARRIER_HEALTH_BAR_HEIGHT = 0.15f;
const float BarrierView::SHROUD_UP_SPEED = 0.03;
const glm::vec3 BarrierView::SHROUD_OFFSET = glm::vec3(-6.0, 6.0, 6.0);
const std::chrono::milliseconds BarrierView::SHROUD_CYCLE =
  std::chrono::milliseconds(3000);

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
                           p + SHROUD_OFFSET,
                           glm::vec3(p.x, p.y, p.z + _scaleFactor),
                           0.05f,
                           5),
  _shroudPos(p), _linesShader(linesShader)
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
  float p;
  if (_animate) {
    if (_timer.elapsed() >= SHROUD_CYCLE) {
      // TODO animation bug
      p = 0.999;
      _setUp = true;
    } else {
      p = static_cast<float>(_timer.elapsed().count()) / SHROUD_CYCLE.count();
    }
  } else {
    p = 0.001;
    _timer.reload();
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _shader.use();
  _shroudModel->animate(_shader, Animation::Type::OneShot, p);
  _shader.configure();
  _shader.setBool("animated", true);
  auto model = glm::mat4(1.0f);
  _shroudPos.z =
    ::min(_position.z + SHROUD_OFFSET.z, _shroudPos.z + SHROUD_UP_SPEED);
  auto xFactor = ::abs(SHROUD_OFFSET.z / SHROUD_OFFSET.x);
  auto yFactor = ::abs(SHROUD_OFFSET.z / SHROUD_OFFSET.y);
  _shroudPos.x = ::max(_position.x + SHROUD_OFFSET.x,
                       _shroudPos.x - SHROUD_UP_SPEED / xFactor);
  _shroudPos.y = ::min(_position.y + SHROUD_OFFSET.y,
                       _shroudPos.y + SHROUD_UP_SPEED / yFactor);
  glm::vec3 co = _shroudPos - _position;
  float oyAngle =
    -M_PI / 2 + ::abs(::atan(co.z / ::sqrt(::pow(co.x, 2) + ::pow(co.y, 2))));
  float ozAngle = M_PI / 2 - ::atan(co.z / co.y);

  model = glm::translate(model, _shroudPos);
  model = glm::rotate(model, -ozAngle, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::rotate(model, oyAngle, glm::vec3(0.0f, 1.0f, 0.0f));
  _shader.setTransformation("model", glm::value_ptr(model));

  _shroudModel->render();
  glDisable(GL_BLEND);
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
  return _setUp;
}

bool BarrierView::onOrbit() const
{
  return (_shroudPos.z == _position.z + SHROUD_OFFSET.z);
}

glm::vec3 BarrierView::shroudPosition() const
{
  return _shroudPos;
}

void BarrierView::startAnimation()
{
  _animate = true;
}
