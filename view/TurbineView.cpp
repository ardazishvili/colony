#include "TurbineView.h"
#include "../fig/globals.h"

float TurbineView::TURBINE_HEALTH_BAR_WIDTH = 1.2f;
float TurbineView::TURBINE_HEALTH_BAR_HEIGHT = 0.15f;
float TurbineView::TURBINE_SCALE_FACTOR = 0.4f;
float TurbineView::TURBINE_MODEL_HEIGHT = 5.7;
std::chrono::milliseconds TurbineView::TURBINE_CYCLE =
  std::chrono::milliseconds(30000);

TurbineView::TurbineView(Shader& textureShader,
                         Shader& linesShader,
                         glm::vec3 p,
                         glm::vec3 spFlat,
                         glm::vec3 spGlobe) :
  StructureView(
    textureShader,
    p,
    0.75,
    { -0.3, 0, TURBINE_HEALTH_BAR_WIDTH, TURBINE_HEALTH_BAR_HEIGHT },
    TexturePackType::PreBuild),
  _linesShader(linesShader), _shroudPosFlat(spFlat), _shroudPosGlobe(spGlobe)
{
  _objScale = TURBINE_SCALE_FACTOR;
  _model = modelLoader->models()[Models::Turbine];
  _model->setActiveTexturesPack(TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");
  _timer.reload();
}

void TurbineView::draw()
{
  if (_timer.elapsed() >= TURBINE_CYCLE) {
    _timer.reload();
  }
  float p =
    static_cast<float>(_timer.elapsed().count()) / TURBINE_CYCLE.count();

  // TODO animation bug
  p = (p == 0) ? p + 0.001 : p;
  p = (p == 1) ? p - 0.001 : p;

  _shader.use();
  _model->animate(_shader, Animation::Type::OneShot, p);
  _shader.configure();
  _shader.setBool("animated", true);
  auto model = glm::mat4(1.0f);
  if (!flatView) {
    model = globeModel();
  } else {
    model = flatModel();
  }
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _model->render();
  showHealthBar();
  if (_beamFlat && _beamGlobe)
    if (!flatView) {
      _beamGlobe->render();
    } else {
      _beamFlat->render();
    }
}

void TurbineView::initBeam()
{
  _beamFlat = std::make_unique<Beam>(
    _linesShader,
    glm::vec3(_position.x,
              _position.y,
              _position.z +
                TURBINE_MODEL_HEIGHT * VIEW_SCALE * TURBINE_SCALE_FACTOR - 0.1),
    _shroudPosFlat,
    0.06f,
    10);
  _beamGlobe = std::make_unique<Beam>(
    _linesShader,
    globeMapper(glm::vec3(
      _position.x,
      _position.y,
      _position.z + TURBINE_MODEL_HEIGHT * VIEW_SCALE * TURBINE_SCALE_FACTOR -
        0.1)),
    globeMapper(_shroudPosGlobe),
    0.06f,
    10);
}
