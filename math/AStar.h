#ifndef ASTAR_H
#define ASTAR_H

#include <map>
#include <optional>

#include "../engine/ObstaclesSegment.h"

struct APoint
{
  APoint(unsigned int xc, unsigned int yc) : x(xc), y(yc)
  {
  }
  unsigned int x;
  unsigned int y;
};

bool operator==(const APoint& lhs, const APoint& rhs);

// f = g + h;
struct ANode
{
  ANode(glm::vec2 vec, APoint point) : p(vec), integerP(point)
  {
  }
  ANode() = delete;
  ANode(const ANode& other) = default;
  ANode(ANode&& other) = default;
  ANode& operator=(const ANode& rhs) = default;
  ANode& operator=(ANode&& rhs) = default;

  glm::vec2 p;
  APoint integerP;
  float g{ 0 };
  float f{ 0 };
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
  std::optional<APath> getPath(glm::vec2 s, glm::vec2 e);

private:
  float h(glm::vec2 c, glm::vec2 goal);
  APath reconstructPath(ANode* current);
  std::vector<ANode> getNeighbors(const ANode* const node);

  const std::vector<VertexColor>& _v;
  const std::vector<bool>& _o;
  SegmentDimensions _sd;

  static const unsigned int MAX_ITER;
};

#endif
