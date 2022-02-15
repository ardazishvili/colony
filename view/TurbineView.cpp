#include "view/TurbineView.h"

#include "fig/globals.h"
#include "figImpl/globals.h"

TurbineView::TurbineView(glm::vec3 p, glm::vec3 spFlat, glm::vec3 spGlobe)
    : StructureView(
          p, 0.75,
          {-0.3, 0, TURBINE_HEALTH_BAR_WIDTH, TURBINE_HEALTH_BAR_HEIGHT},
          fig::TexturePackType::PreBuild),
      _shroudPosFlat(spFlat),
      _shroudPosGlobe(spGlobe) {
  _objScale = TURBINE_SCALE_FACTOR;
  _model = fig::modelLoader->models()[fig::Models::Turbine];
  _model->setActiveTexturesPack(fig::TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture(fig::assets_dir + "/red.png");
  _timer.reload();
}

void TurbineView::draw() {
  if (_timer.elapsed() >= TURBINE_CYCLE) {
    _timer.reload();
  }
  float p =
      static_cast<float>(_timer.elapsed().count()) / TURBINE_CYCLE.count();

  // TODO animation bug
  p = (p == 0) ? p + 0.001 : p;
  p = (p == 1) ? p - 0.001 : p;

  _shader.use();
  _model->animate(_shader, fig::Animation::Type::OneShot, p);
  _shader.configure();
  _shader.setBool("animated", true);
  auto model = glm::mat4(1.0f);
  model = flatView ? flatModel() : globeModel();
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

void TurbineView::initBeam() {
  _beamFlat = std::make_unique<fig::Beam>(
      *SHADERS_MAP[ShaderType::LINES],
      glm::vec3(_position.x, _position.y,
                _position.z +
                    TURBINE_MODEL_HEIGHT * VIEW_SCALE * TURBINE_SCALE_FACTOR -
                    0.1),
      _shroudPosFlat, 0.06f, 10);
  _beamGlobe = std::make_unique<fig::Beam>(
      *SHADERS_MAP[ShaderType::LINES],
      globeMapper(glm::vec3(
          _position.x, _position.y,
          _position.z +
              TURBINE_MODEL_HEIGHT * VIEW_SCALE * TURBINE_SCALE_FACTOR - 0.1)),
      globeMapper(_shroudPosGlobe), 0.06f, 10);
}
