#include "../imgui/imgui.h"

#include "../engine/Circle.h"
#include "../globals.h"
#include "BarrierView.h"

float BarrierView::BARRIER_HEALTH_BAR_WIDTH = 1.2f;
float BarrierView::BARRIER_HEALTH_BAR_HEIGHT = 0.15f;
float BarrierView::BARRIER_SCALE_INCREMENT = 1.0f;
float BarrierView::BARRIER_INIT_SCALE = 1.0f;
const float BarrierView::SHROUD_UP_SPEED = 0.09;
const glm::vec3 BarrierView::SHROUD_OFFSET = glm::vec3(-6.0, 6.0, 6.0);
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

glm::vec3 mapper(glm::vec3 p)
{
  float R = 4.0 * 3.1415;
  float S = 6.0 * 3.1415;
  float longitude = p.x * sqrt(2.0f) / R;
  float latitude = 2 * atan(p.y / (R * (1 + sqrt(2) / 2.0f)));

  return glm::vec3((S + p.z) * cos(latitude) * cos(longitude),
                   (S + p.z) * cos(latitude) * sin(longitude),
                   (S + p.z) * sin(latitude));
}

float xs(float xStart, float xEnd)
{
  float R = 4.0 * 3.1415;
  float S = 6.0 * 3.1415;
  float longStart = xStart * sqrt(2.0f) / R;
  float longEnd = xEnd * sqrt(2.0f) / R;
  return S * (longEnd - longStart);
}

float ys(float yStart, float yEnd)
{
  float R = 4.0 * 3.1415;
  float S = 6.0 * 3.1415;
  float latStart = 2 * atan(yStart / (R * (1 + sqrt(2) / 2.0f)));
  float latEnd = 2 * atan(yEnd / (R * (1 + sqrt(2) / 2.0f)));
  std::cout << "latStart= " << latStart << std::endl;
  std::cout << "latEnd= " << latEnd << std::endl;
  return S * (latEnd - latStart);
}

void BarrierView::draw()
{
  static bool bd = true;
  static float a = 1.0f;
  static float b = 1.0f;
  ImGui::Begin("Barriers display");
  ImGui::SetWindowPos(ImVec2(0, 640));
  ImGui::SetWindowSize(ImVec2(200, 80));
  ImGui::Checkbox("state", &bd);
  ImGui::SliderFloat("a", &a, 0, 4);
  ImGui::SliderFloat("b", &b, 0, 4);
  ImGui::End();
  /* std::cout << "_position.x= " << _position.x << std::endl; */
  /* std::cout << "_position.y= " << _position.y << std::endl; */
  auto p = _position;
  auto dx = glm::distance(mapper(glm::vec3(p.x - 1, p.y, p.z)),
                          mapper(glm::vec3(p.x + 1, p.y, p.z))) /
            2;
  /* std::cout << "dx= " << dx << std::endl; */
  auto dy = glm::distance(mapper(glm::vec3(p.x, p.y - 1, p.z)),
                          mapper(glm::vec3(p.x, p.y + 1, p.z))) /
            2;
  /* std::cout << "dy= " << dy << std::endl; */
  auto xss = xs(p.x - 1, p.x + 1);
  auto yss = ys(p.y - 1, p.y + 1);
  std::cout << "xs(p.x -1, p.x + 1)= " << xss << std::endl;
  std::cout << "ys(p.y -1, p.y + 1)= " << yss << std::endl;

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
      model = glm::scale(model, glm::vec3(1.552 / h(lat), 1.552 / k(lat), 1));
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
