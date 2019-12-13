#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include "Mesh.h"
/* #include "ModelMesh.h" */
#include "SubTerrainMesh.h"

class TerrainMesh : public Mesh
{
public:
  /* TerrainMesh(); */
  /* ~TerrainMesh(); */
  void render();
  void initTerrain(float bottomLeftX,
                   float bottomLeftY,
                   float topRightX,
                   float topRightY,
                   int divisions,
                   float xyScale,
                   float zScale);
  float getZ(float x, float y) const;
  glm::vec3 getRgbColor(float x, float y) const;
  void deselect();
  static float UPDATE_COLOR_SPEED;
  static float plantsColor[3];
  SubTerrainMesh _subTerrainMesh;

  const static glm::vec4 SELECTION_COLOR;
  const static glm::vec4 DESELECTION_COLOR;
  const static glm::vec4 DEFAULT_BARRIER_COLOR;

private:
  /* void deinit(); */
  std::vector<VertexColor> _v;
  std::vector<unsigned int> _indices;
  float _width;
  float _height;
  unsigned int _latticeWidth;
  unsigned int _latticeHeight;
  float _xStep;
  float _yStep;
  float _xyScale;
  float _zScale;
  /* GLuint _vao; */
  /* GLuint _vertexVbo; */
  /* GLuint _indicesEbo; */
};

#endif
