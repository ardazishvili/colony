#include "TankFactoryView.h"
#include "../globals.h"

float TankFactoryView::TANK_FACTORY_HEALTH_BAR_WIDTH = 1.2f;
float TankFactoryView::TANK_FACTORY_HEALTH_BAR_HEIGHT = 0.15f;

TankFactoryView::TankFactoryView(Shader& shader, glm::vec3 position) :
  StructureView(
    shader,
    position,
    1.41 / 2,
    { -0.3, 0, TANK_FACTORY_HEALTH_BAR_WIDTH, TANK_FACTORY_HEALTH_BAR_HEIGHT },
    TexturePackType::PreBuild)
{
  _model = modelLoader->models()[Models::TankFactory];
  _model->setActiveTexturesPack(TexturePackType::PreBuild);
  _healthBar.setOffsetZ(1.3f);
  _healthBar.setTexture("/home/roman/repos/colony/assets/red.png");
}

void TankFactoryView::draw()
{
  _shader.use();
  _shader.configure();
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  if (!flatView) {
    model = glm::translate(model, position());
    model = glm::rotate(
      model, glm::radians(_angle + 90), glm::vec3(glm::normalize(position())));
    model = glm::rotate(model, longitude(), glm::vec3(0, 0, 1));
    model = glm::rotate(
      model, -latitude() + static_cast<float>(M_PI / 2), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(VIEW_SCALE));
  } else {
    model = glm::translate(model, position());
    model =
      glm::rotate(model, glm::radians(_angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(VIEW_SCALE));
  }
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _model->render();
  showHealthBar();
}

