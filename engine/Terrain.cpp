#include "Terrain.h"

Terrain::Terrain(Shader shader,
                 float bottomLeftX,
                 float bottomLeftY,
                 float topRightX,
                 float topRightY,
                 int divisions) :
  _shader(shader),
  _bottomLeft(bottomLeftX, bottomLeftY), _topRight(topRightX, topRightY)
{
  _mesh.initTerrain(
    0, 0, topRightX - bottomLeftX, topRightY - bottomLeftY, divisions);
  _offset.x = bottomLeftX;
  _offset.y = bottomLeftY;
}

void Terrain::render()
{
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset);
  model =
    glm::rotate(model, glm::radians(_yawAngle), glm::vec3(0.0, 0.0f, 1.0f));
  model =
    glm::rotate(model, glm::radians(_pitchAngle), glm::vec3(1.0, 0.0f, 0.0f));
  model = glm::scale(model, glm::vec3(_xScaleFactor, _yScaleFactor, 1.0f));
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _shader.use();
  _mesh.render();
}

void Terrain::setOffsetZ(float offset)
{
  _offset.z = offset;
}

void Terrain::setPitchAngle(float angle)
{
  _pitchAngle = angle;
}

void Terrain::setYawAngle(float angle)
{
  _yawAngle = angle;
}

void Terrain::setOffsetXY(float x, float y)
{
  _offset.x = x;
  _offset.y = y;
}

void Terrain::setScaleX(float factor)
{
  _xScaleFactor = factor;
}

glm::vec4 Terrain::getArea() const
{
  return glm::vec4(::min(_offset.x, _offset.x + _xScaleFactor),
                   ::min(_offset.y, _offset.y + _yScaleFactor),
                   ::max(_offset.x, _offset.x + _xScaleFactor),
                   ::max(_offset.y, _offset.y + _yScaleFactor));
}

void Terrain::setScaleXY(float xFactor, float yFactor)
{
  _xScaleFactor = xFactor;
  _yScaleFactor = yFactor;
}
