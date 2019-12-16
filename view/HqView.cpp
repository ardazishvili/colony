#include "HqView.h"
#include "../globals.h"

std::map<Status, unsigned int> hqTexturesMap;
unsigned int hqSetAngleTexture;
float HqView::HQ_HEALTH_BAR_WIDTH = 1.2f;
float HqView::HQ_HEALTH_BAR_HEIGHT = 0.15f;

HqView::HqView(Shader& shader, glm::vec3 position) :
  StructureView(shader,
                position,
                0.75,
                { -0.3, 0, HQ_HEALTH_BAR_WIDTH, HQ_HEALTH_BAR_HEIGHT },
                TexturePackType::PreBuild)
{
  _model = modelLoader->models()[Models::Hq];
  _model->setActiveTexturesPack(TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");
}

void HqView::draw()
{
  _shader.use();
  _shader.configure();
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::rotate(model, glm::radians(_angle), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(VIEW_SCALE));
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _shader.use();
  _model->render();
  showHealthBar();
}
