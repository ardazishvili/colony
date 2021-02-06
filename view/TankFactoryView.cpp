#include "../fig/globals.h"

#include "../figImpl/globals.h"
#include "TankFactoryView.h"

float TankFactoryView::TANK_FACTORY_HEALTH_BAR_WIDTH = 1.2f;
float TankFactoryView::TANK_FACTORY_HEALTH_BAR_HEIGHT = 0.15f;

TankFactoryView::TankFactoryView(fig::Shader& shader, glm::vec3 position) :
  StructureView(shader,
                position,
                1.41 / 2,
                { -0.3, 0, TANK_FACTORY_HEALTH_BAR_WIDTH, TANK_FACTORY_HEALTH_BAR_HEIGHT },
                fig::TexturePackType::PreBuild)
{
  _model = fig::modelLoader->models()[fig::Models::TankFactory];
  _model->setActiveTexturesPack(fig::TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture(fig::assets_dir + "/red.png");
}

void TankFactoryView::draw()
{
  _shader.use();
  _shader.configure();
  _shader.setBool("animated", false);
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
}
