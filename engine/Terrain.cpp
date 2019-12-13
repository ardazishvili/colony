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
  _mesh._subTerrainMesh.render();
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}

glm::vec3 Terrain::getXYZ(glm::vec2 xy) const
{
  return glm::vec3(xy.x, xy.y, _mesh.getZ(xy.x - _offset.x, xy.y - _offset.y));
}

glm::vec3 Terrain::getRgbColor(float x, float y) const
{
  return _mesh.getRgbColor(x, y);
}

void Terrain::updateColor(unsigned int index)
{
  _mesh.updateColor(index);
}

void Terrain::selectSubTerrainRegion(RectangleRegion region, glm::vec4 rgba)
{
  _mesh._subTerrainMesh.selectSubTerrainRegion(region, rgba);
}

std::shared_ptr<LivingArea> Terrain::addLivingArea(CircularRegion region,
                                                   glm::vec4 rgba)
{
  return _mesh._subTerrainMesh.addLivingArea(region, rgba);
}

void Terrain::updateLivingArea(std::shared_ptr<LivingArea> area)
{
  _mesh._subTerrainMesh.updateLivingArea(area);
}

void Terrain::deselect()
{
  _mesh._subTerrainMesh.deselect();
}
