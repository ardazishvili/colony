#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "../globals.h"
#include "TurbineView.h"

float TurbineView::TURBINE_HEALTH_BAR_WIDTH = 1.2f;
float TurbineView::TURBINE_HEALTH_BAR_HEIGHT = 0.15f;
float TurbineView::TURBINE_SCALE_FACTOR = 0.4f;
float TurbineView::TURBINE_MODEL_HEIGHT = 5.7;
std::chrono::milliseconds TurbineView::TURBINE_CYCLE =
  std::chrono::milliseconds(30000);

TurbineView::TurbineView(Shader& textureShader,
                         Shader& linesShader,
                         glm::vec3 p,
                         glm::vec3 sp) :
  StructureView(
    textureShader,
    p,
    0.75,
    { -0.3, 0, TURBINE_HEALTH_BAR_WIDTH, TURBINE_HEALTH_BAR_HEIGHT },
    TexturePackType::PreBuild),
  _linesShader(linesShader),
  _beam(linesShader,
        glm::vec3(
          p.x,
          p.y,
          p.z + TURBINE_MODEL_HEIGHT * VIEW_SCALE * TURBINE_SCALE_FACTOR - 0.1),
        glm::vec3(sp.x, sp.y, sp.z),
        0.06f,
        10)
{
  std::cout << "sp.x= " << sp.x << std::endl;
  std::cout << "sp.y= " << sp.y << std::endl;
  std::cout << "sp.z= " << sp.z << std::endl;
  std::cout << "p.x= " << p.x << std::endl;
  std::cout << "p.y= " << p.y << std::endl;
  std::cout << "p.z= "
            << p.z + TURBINE_MODEL_HEIGHT * VIEW_SCALE * TURBINE_SCALE_FACTOR -
                 0.1
            << std::endl;
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
  model = glm::translate(model, _position);
  model = glm::rotate(model, glm::radians(_angle), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(VIEW_SCALE * TURBINE_SCALE_FACTOR));
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->setActiveTexturesPack(_texturesType);
  _model->render();
  showHealthBar();
  _beam.render();
}
