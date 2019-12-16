#include "TurbineView.h"
#include "../globals.h"

float TurbineView::TURBINE_HEALTH_BAR_WIDTH = 1.2f;
float TurbineView::TURBINE_HEALTH_BAR_HEIGHT = 0.15f;

TurbineView::TurbineView(Shader& textureShader,
                         Shader& linesShader,
                         glm::vec3 position) :
  StructureView(
    textureShader,
    position,
    0.75,
    { -0.3, 0, TURBINE_HEALTH_BAR_WIDTH, TURBINE_HEALTH_BAR_HEIGHT },
    TexturePackType::PreBuild),
  _linesShader(linesShader)
{
  _model = modelLoader->models()[Models::Turbine];
  _model->setActiveTexturesPack(TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");
}

void TurbineView::draw()
{
  _shader.use();
  _shader.configure();
  /* _shader.setBool("animated", true); */
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::rotate(model, glm::radians(_angle), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(VIEW_SCALE));
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _model->render();
  showHealthBar();
}
