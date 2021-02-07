#include "../fig/Circle.h"
#include "../fig/globals.h"
#include "../fig/third/gui/imgui/imgui.h"

#include "../figImpl/globals.h"
#include "BarrierView.h"

float BarrierView::BARRIER_HEALTH_BAR_WIDTH = 1.2f;
float BarrierView::BARRIER_HEALTH_BAR_HEIGHT = 0.15f;
float BarrierView::BARRIER_SCALE_INCREMENT = 1.0f;
float BarrierView::BARRIER_INIT_SCALE = 1.0f;

BarrierView::BarrierView(glm::vec3 p, fig::Terrain* terrain) :
  StructureView(p,
                BARRIER_INIT_SCALE,
                { -0.3, 0, BARRIER_HEALTH_BAR_WIDTH, BARRIER_HEALTH_BAR_HEIGHT },
                fig::TexturePackType::Initial),
  _terrain(terrain), _linesShader(*SHADERS_MAP[ShaderType::LINES])
{
  _model = fig::modelLoader->models()[fig::Models::Barrier];
  _model->setActiveTexturesPack(fig::TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture(fig::assets_dir + "/red.png");
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
      model = glm::rotate(model, -lat + static_cast<float>(M_PI / 2.0), glm::vec3(0, 1, 0));
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

float BarrierView::radius() const
{
  return _scaleFactor;
}

void BarrierView::grow(std::shared_ptr<fig::LivingArea> area)
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
