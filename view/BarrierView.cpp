#include "../imgui/imgui.h"

#include "../engine/Circle.h"
#include "../globals.h"
#include "BarrierView.h"

float BarrierView::BARRIER_HEALTH_BAR_WIDTH = 1.2f;
float BarrierView::BARRIER_HEALTH_BAR_HEIGHT = 0.15f;
float BarrierView::BARRIER_SCALE_INCREMENT = 1.0f;
float BarrierView::BARRIER_INIT_SCALE = 1.0f;
const float BarrierView::SHROUD_UP_SPEED = 0.09;
// z coordinate MUST be equal for FLAT and GLOBE offsets
const glm::vec3 BarrierView::SHROUD_FLAT_OFFSET = glm::vec3(-12.0, 12.0, 12.0);
const glm::vec3 BarrierView::SHROUD_GLOBE_OFFSET = glm::vec3(0, 0, 12.0);
const std::chrono::milliseconds BarrierView::SHROUD_CYCLE =
  std::chrono::milliseconds(1000);

BarrierView::BarrierView(Shader& textureShader,
                         Shader& linesShader,
                         glm::vec3 p,
                         Terrain* terrain) :
  StructureView(
    textureShader,
    p,
    BARRIER_INIT_SCALE,
    { -0.3, 0, BARRIER_HEALTH_BAR_WIDTH, BARRIER_HEALTH_BAR_HEIGHT },
    TexturePackType::Initial),
  _terrain(terrain), _beamFlat(linesShader,
                               p + SHROUD_FLAT_OFFSET,
                               glm::vec3(p.x, p.y, p.z + _scaleFactor),
                               0.05f,
                               5),
  _beamGlobe(linesShader,
             globeMapper(p + SHROUD_GLOBE_OFFSET),
             globeMapper(glm::vec3(p.x, p.y, p.z + _scaleFactor)),
             0.05f,
             5),
  _shroudPosFlat(p), _shroudPosGlobe(p), _linesShader(linesShader)
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
  ImGui::SetWindowPos(ImVec2(0, 640));
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
    model = glm::translate(model, position());
    auto lat = latitude();
    if (!flatView) {
      model = glm::rotate(model, longitude(), glm::vec3(0, 0, 1));
      model = glm::rotate(
        model, -lat + static_cast<float>(M_PI / 2.0), glm::vec3(0, 1, 0));
      model = glm::scale(model, glm::vec3(_scaleFactor));
      model = glm::scale(model, glm::vec3(1.5 / h(lat), 1.5 / k(lat), 1));
    } else {
      model = glm::rotate(model, glm::radians(_angle), glm::vec3(0, 0, 1));
      model = glm::scale(model, glm::vec3(_scaleFactor));
    }
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
  _shroudPosFlat.z = ::min(_position.z + SHROUD_FLAT_OFFSET.z,
                           _shroudPosFlat.z + SHROUD_UP_SPEED);
  _shroudPosGlobe.z = _shroudPosFlat.z;

  auto model = glm::mat4(1.0f);
  if (!flatView) {
    auto sp = globeMapper(_shroudPosGlobe);
    model = glm::translate(model, sp);
    model = glm::rotate(
      model, glm::radians(_angle + 90), glm::vec3(glm::normalize(position())));
    model = glm::rotate(
      model, _shroudPosGlobe.x * sqrt(2.0f) / R, glm::vec3(0, 0, 1));
    model =
      glm::rotate(model,
                  -static_cast<float>(
                    2 * atan(_shroudPosGlobe.y / (R * (1 + sqrt(2) / 2.0f)))) +
                    static_cast<float>(M_PI / 2),
                  glm::vec3(0, 1, 0));
  } else {
    auto xFactor = ::abs(SHROUD_FLAT_OFFSET.z / SHROUD_FLAT_OFFSET.x);
    auto yFactor = ::abs(SHROUD_FLAT_OFFSET.z / SHROUD_FLAT_OFFSET.y);
    _shroudPosFlat.x = ::max(_position.x + SHROUD_FLAT_OFFSET.x,
                             _shroudPosFlat.x - SHROUD_UP_SPEED / xFactor);
    _shroudPosFlat.y = ::min(_position.y + SHROUD_FLAT_OFFSET.y,
                             _shroudPosFlat.y + SHROUD_UP_SPEED / yFactor);
    glm::vec3 co = _shroudPosFlat - _position;
    float oyAngle =
      -M_PI / 2 + ::abs(::atan(co.z / ::sqrt(::pow(co.x, 2) + ::pow(co.y, 2))));
    float ozAngle = M_PI / 2 - ::atan(co.z / co.y);
    model = glm::translate(model, _shroudPosFlat);
    model = glm::rotate(model, -ozAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, oyAngle, glm::vec3(0.0f, 1.0f, 0.0f));
  }
  _shader.setTransformation("model", glm::value_ptr(model));

  _shroudModel->render();
  glDisable(GL_BLEND);
}

void BarrierView::drawBeam()
{
  if (!flatView) {
    _beamGlobe.render();
  } else {
    _beamFlat.render();
  }
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
  return (_shroudPosFlat.z == _position.z + SHROUD_FLAT_OFFSET.z);
}

glm::vec3 BarrierView::shroudPositionFlat() const
{
  return _shroudPosFlat;
}

glm::vec3 BarrierView::shroudPositionGlobe() const
{
  return _shroudPosGlobe;
}

void BarrierView::startAnimation()
{
  _animate = true;
}

void BarrierView::grow(std::shared_ptr<LivingArea> area)
{
  _growFuture = std::async(std::launch::async, [this, area]() {
    auto finalScale = _scaleFactor + BARRIER_SCALE_INCREMENT;
    while (_scaleFactor < finalScale) {
      _scaleFactor += 0.01;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    _terrain->growLivingArea(area, _scaleFactor);
    _selectionRadius = _scaleFactor;
  });
}
