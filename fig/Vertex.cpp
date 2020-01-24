#include "Vertex.h"

Vertex::Vertex()
{
  Reset();
};

void Vertex::Reset()
{
  for (int i = 0; i < NUM_BONES_PER_VERTEX; ++i) {
    IDs[i] = 0;
    Weights[i] = 0;
  }
}

void Vertex::AddBoneData(unsigned int BoneID, float Weight)
{
  for (unsigned int i = 0; i < NUM_BONES_PER_VERTEX; i++) {
    if (Weights[i] == 0.0) {
      IDs[i] = BoneID;
      Weights[i] = Weight;
      return;
    }
  }

  // should never get here - more bones than we have space for
  assert(0);
}
