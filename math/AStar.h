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

using APath = std::vector<glm::vec2>;
class AStar
{
public:
  AStar(const std::vector<VertexColor>& v,
        const std::vector<bool>& o,
        SegmentDimensions sd);
  // Get path from start to end
  APath getPath(glm::vec2 s, glm::vec2 e);

private:
  float h(glm::vec2 c, glm::vec2 goal);
  const std::vector<VertexColor>& _v;
  const std::vector<bool>& _o;
  SegmentDimensions _sd;
};

#endif
