#include "Terrain.h"

Terrain::Terrain(Shader& shader,
                 float bottomLeftX,
                 float bottomLeftY,
                 float topRightX,
                 float topRightY,
                 int divisions,
                 float xyScale,
                 float zScale) :
  _shader(shader),
  _xyScale(xyScale), _zScale(zScale)
{
  _mesh.initTerrain(0,
                    0,
                    topRightX - bottomLeftX,
                    topRightY - bottomLeftY,
                    divisions,
                    xyScale,
                    zScale);
  _offset.x = bottomLeftX;
  _offset.y = bottomLeftY;
}

void Terrain::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset * _xyScale);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _mesh.render();
}

void Terrain::renderSub()
{
  _shader.use();
  _shader.configure();
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset * _xyScale);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _mesh.renderSub();
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}

glm::vec3 Terrain::getXYZ(glm::vec2 xy) const
{
  return glm::vec3(xy.x, xy.y, _mesh.getZ(xy.x - _offset.x, xy.y - _offset.y));
}

/* void Terrain::updateColor(glm::vec2 xy) */
/* { */
/*   _mesh.updateColor(xy.x, xy.y); */
/* } */

void Terrain::updateColor(unsigned int index)
{
  _mesh.updateColor(index);
}

std::vector<unsigned int> Terrain::getVertices(glm::vec2 center, float radius)
{
  return _mesh.getVertices(center, radius);
}

void Terrain::selectSubTerrainRegion(Region region, float alfa)
{
  _mesh.selectSubTerrainRegion(region, alfa);
}

void Terrain::deselect()
{
  _mesh.deselect();
}
