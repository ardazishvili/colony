#include "HqView.h"
#include "../fig/globals.h"
#include "../figImpl/globals.h"

float HqView::HQ_HEALTH_BAR_WIDTH = 1.2f;
float HqView::HQ_HEALTH_BAR_HEIGHT = 0.15f;

HqView::HqView(fig::Shader& shader, glm::vec3 position) :
  StructureView(shader,
                position,
                0.75,
                { -0.3, 0, HQ_HEALTH_BAR_WIDTH, HQ_HEALTH_BAR_HEIGHT },
                fig::TexturePackType::PreBuild)
{
  _model = fig::modelLoader->models()[fig::Models::Hq];
  _model->setActiveTexturesPack(fig::TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture(fig::assets_dir + "/red.png");
}

void HqView::draw()
{
  _shader.use();
  _shader.configure();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  if (!flatView) {
    model = globeModel();
  } else {
    model = flatModel();
  }
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _shader.use();
  _model->render();
  glDisable(GL_BLEND);
  showHealthBar();
}
