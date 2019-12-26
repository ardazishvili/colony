#ifndef ASTAR_H
#define ASTAR_H

#include "../engine/ObstaclesSegment.h"

// f = g + h;
struct ANode
{
  float x;
  float y;
  float h{ 0 };
  float g{ 0 };
  float f{ 0 };
  bool isObstacle{ false };
  ANode* parent{ nullptr };
};

class AStar
{
public:
  AStar() = default;
  void init(const std::vector<VertexColor>& v,
            const std::vector<bool>& o,
            SegmentDimensions sd);
};

#endif
