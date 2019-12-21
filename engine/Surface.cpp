#include "Surface.h"
#include "../globals.h"

Surface::Surface(Camera& camera,
                 Shader& shader,
                 float bottomLeftX,
                 float bottomLeftY,
                 float topRightX,
                 float topRightY,
                 int divisions,
                 std::string texturePath) :
  _camera(camera),
  _shader(shader), _bottomLeft(bottomLeftX, bottomLeftY),
  _topRight(topRightX, topRightY)
{
  _mesh.initSurface(0,
                    0,
                    topRightX - bottomLeftX,
                    topRightY - bottomLeftY,
                    divisions,
                    texturePath);
  _offset.x = bottomLeftX;
  _offset.y = bottomLeftY;
}

void Surface::render()
{
  _yawAngle = _camera.getYaw() - 90;
  _pitchAngle = -_camera.getPitch();
  /* logger._log.AddLog("pitch: %f \n", _pitchAngle); */
  /* logger._log.AddLog("yaw: %f \n", _yawAngle); */

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

void Surface::setOffsetZ(float offset)
{
  _offset.z = offset;
}

void Surface::setTexture(const std::string& filename)
{
  _mesh.loadTexture(filename, TexturePackType::Initial);
}

/* void Surface::setPitchAngle() */
/* { */
/*   _pitchAngle = -_camera.getPitch(); */
/* } */

/* void Surface::setYawAngle(float angle) */
/* { */
/*   _yawAngle = angle; */
/* } */

void Surface::setOffsetXY(float x, float y)
{
  _offset.x = x;
  _offset.y = y;
}

void Surface::setScaleX(float factor)
{
  _xScaleFactor = factor;
}

void Surface::setScaleXY(float xFactor, float yFactor)
{
  _xScaleFactor = xFactor;
  _yScaleFactor = yFactor;
}
