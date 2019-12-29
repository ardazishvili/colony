#include <iomanip>
#include <set>

#include "../globals.h"
#include "AStar.h"

const unsigned int AStar::MAX_ITER = 2000;

AStar::AStar(const std::vector<VertexColor>& v,
             const std::vector<bool>& o,
             SegmentDimensions sd) :
  _v(v),
  _o(o), _sd(sd)
{
}

std::optional<APath> AStar::getPath(glm::vec2 s, glm::vec2 e)
{
  s.x += _sd.xOffset;
  s.y += _sd.yOffset;
  e.x += _sd.xOffset;
  e.y += _sd.yOffset;
  auto result = APath();

  unsigned int sxi = s.x / _sd.xStep;
  unsigned int syi = s.y / _sd.yStep;
  auto start = std::make_shared<ANode>(s, APoint{ sxi, syi });
  unsigned int exi = e.x / _sd.xStep;
  unsigned int eyi = e.y / _sd.yStep;
  auto end = std::make_shared<ANode>(e, APoint{ exi, eyi });
  start->g = 0;
  start->f = start->g + h(start->p, end->p);

  auto comp = [](const std::shared_ptr<ANode>& lhs,
                 const std::shared_ptr<ANode>& rhs) {
    return lhs->f < rhs->f;
  };
  auto frontier = std::set<std::shared_ptr<ANode>, decltype(comp)>(comp);
  frontier.emplace(start);
  std::set<std::shared_ptr<ANode>> closed;

  unsigned int it = 0;
  while (!frontier.empty()) {
    ++it;
    // TODO add more elegant solution
    if (it > MAX_ITER) {
      break;
    }
    auto currentIt = frontier.begin();
    auto current = *currentIt;

    if (current->integerP == end->integerP) {
      return reconstructPath(current.get());
    }

    closed.insert(current);
    frontier.erase(currentIt);
    auto neighbors = getNeighbors(current.get());
    for (auto& n : neighbors) {
      auto tmp = current->g + _sd.xStep;
      auto fIt = std::find_if(
        frontier.begin(), frontier.end(), [&n](std::shared_ptr<ANode> node) {
          return (node->integerP == n.integerP);
        });
      if (fIt != frontier.end() && tmp < (*fIt)->g) {
        frontier.erase(fIt);
      }
      auto cIt = std::find_if(
        closed.begin(), closed.end(), [&n](std::shared_ptr<ANode> node) {
          return (node->integerP == n.integerP);
        });
      if (cIt != closed.end() && tmp < (*cIt)->g) {
        closed.erase(cIt);
      }
      if (fIt == frontier.end() && cIt == closed.end()) {
        auto a = std::make_shared<ANode>(n);
        a->g = tmp;
        a->f = tmp + h(a->p, end->p);
        a->parent = current.get();
        frontier.insert(a);
      }
    }
  }

  return std::nullopt;
}

float AStar::h(glm::vec2 c, glm::vec2 goal)
{
  return glm::distance(c, goal);
}

APath AStar::reconstructPath(ANode* current)
{
  auto path = APath();
  while (current->parent != nullptr) {
    auto p = glm::vec2(current->p.x - _sd.xOffset, current->p.y - _sd.yOffset);
    path.push_back(p);
    current = current->parent;
  }

  return path;
}

bool operator==(const APoint& lhs, const APoint& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

/* bool operator<(const std::shared_ptr<ANode>& lhs, */
/*                const std::shared_ptr<ANode>& rhs) */
/* { */
/*   return lhs->f < rhs->f; */
/* } */

std::vector<ANode> AStar::getNeighbors(const ANode* const current)
{
  auto cx = current->integerP.x;
  auto cy = current->integerP.y;
  struct Offset
  {
    int x;
    int y;
  };
  std::vector<Offset> offsets = { { -1, 0 },  { 1, 0 },  { 0, -1 }, { 0, 1 },
                                  { -1, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 } };
  std::vector<ANode> res;
  for (auto& offset : offsets) {

    unsigned int i = cx + offset.x;
    unsigned int j = cy + offset.y;
    if (!_o.at(i * _sd.latticeWidth + j)) {
      float x = _v.at(i * _sd.latticeWidth + j).p.x;
      float y = _v.at(i * _sd.latticeWidth + j).p.y;
      auto n = ANode(glm::vec2(x, y), APoint(i, j));
      res.push_back(n);
    }
  }
  return res;
}
