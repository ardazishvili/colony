#include "ShroudView.h"
#include "../globals.h"

const std::chrono::milliseconds ShroudView::SHROUD_CYCLE =
  std::chrono::milliseconds(1000);
float ShroudView::HEALTH_BAR_WIDTH = 0.5;
float ShroudView::HEALTH_BAR_HEIGHT = 0.04;
const glm::vec3 ShroudView::SHROUD_FLAT_OFFSET = glm::vec3(-12.0, 12.0, 12.0);
const glm::vec3 ShroudView::SHROUD_GLOBE_OFFSET = glm::vec3(0, 0, 12.0);
const float ShroudView::SHROUD_UP_SPEED = 0.09;

ShroudView::ShroudView(Shader& textureShader,
                       Shader& linesShader,
                       glm::vec3 p) :
  UnitView(textureShader,
           p,
           0.38,
           { 0, 0, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT },
           TexturePackType::Initial),
  _shroudPosFlat(p), _shroudPosGlobe(p),
  _beamFlat(linesShader,
            p + SHROUD_FLAT_OFFSET,
            // FIXME add barrier height to beam end's z coordinate
            glm::vec3(p.x, p.y, p.z),
            0.05f,
            5),
  _beamGlobe(linesShader,
             globeMapper(p + SHROUD_GLOBE_OFFSET),
             // FIXME add barrier height to beam end's z coordinate
             globeMapper(glm::vec3(p.x, p.y, p.z)),
             0.05f,
             5)
{
  _shroudModel = modelLoader->models()[Models::Shroud];
  _shroudModel->setActiveTexturesPack(TexturePackType::Initial);
  _hasAnimation = true;
  _healthBar.setOffsetZ(p.z + 0.3);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");
}

void ShroudView::draw()
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

  if (_setUp) {
    drawBeam();
  }
}
glm::vec3 ShroudView::shroudPositionFlat() const
{
  return _shroudPosFlat;
}

glm::vec3 ShroudView::shroudPositionGlobe() const
{
  return _shroudPosGlobe;
}

void ShroudView::startAnimation()
{
  _animate = true;
}

void ShroudView::drawBeam()
{
  if (!flatView) {
    _beamGlobe.render();
  } else {
    _beamFlat.render();
  }
}

bool ShroudView::shroudSetUp() const
{
  return _setUp;
}

bool ShroudView::onOrbit() const
{
  return (_shroudPosFlat.z == _position.z + SHROUD_FLAT_OFFSET.z);
}
