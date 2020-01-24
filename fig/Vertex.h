#ifndef VERTEX_H
#define VERTEX_H

#define NUM_BONES_PER_VERTEX 10

#include <glm/glm.hpp>

struct Vertex
{
  Vertex();
  void Reset();
  void AddBoneData(unsigned int BoneID, float Weight);

  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
  unsigned int IDs[NUM_BONES_PER_VERTEX];
  float Weights[NUM_BONES_PER_VERTEX];
};

#endif
