#include "BarrierView.h"
#include "../engine/Circle.h"
#include "../globals.h"

BarrierView::BarrierView(Shader& textureShader,
                         Shader& colorShader,
                         glm::vec3 position) :
  _textureShader(textureShader),
  _colorShader(colorShader), _position(position)
{
  _model = modelLoader->models()[Models::Barrier];
}

void BarrierView::draw()
{
  _colorShader.use();
  _colorShader.configure();
  auto pos = _position;
  pos.z += 0.05;
  auto c = Circle(_colorShader, pos, _scaleFactor, 20);
  c.render();

  _textureShader.use();
  _textureShader.configure();
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _textureShader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(_scaleFactor));
  _textureShader.setTransformation("model", glm::value_ptr(model));
  _model->render();
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}
glm::vec2 BarrierView::position() const
{
  return glm::vec2(_position.x, _position.y);
}
