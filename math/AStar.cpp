#include <iomanip>
#include <set>

#include "../globals.h"
#include "AStar.h"

AStar::AStar(const std::vector<VertexColor>& v,
             const std::vector<bool>& o,
             SegmentDimensions sd) :
  _v(v),
  _o(o), _sd(sd)
{
  /* std::cout << "v.size= " << v.size() << std::endl; */
  /* ANode node[sd.divisionsX + 1][sd.divisionsY + 1]; */
  /* for (unsigned int i = 0; i < sd.divisionsX + 1; ++i) { */
  /*   for (unsigned int j = 0; j < sd.divisionsY + 1; ++j) { */
  /*     node[i][j].x = v.at(i * sd.latticeWidth + j).p.x; */
  /*     node[i][j].y = v.at(i * sd.latticeWidth + j).p.y; */
  /*     if (o.at(i * sd.latticeWidth + j)) { */
  /*       node[i][j].isObstacle = true; */
  /*     } */
  /*   } */
  /* } */

  /* for (unsigned int i = 0; i < sd.divisionsX + 1; ++i) { */
  /*   for (unsigned int j = 0; j < sd.divisionsY + 1; ++j) { */
  /*     std::cout << setw(15) << setprecision(3) << "(" */
  /*               << v.at(i * _sd.latticeWidth).p.x << "," */
  /*               << v.at(i * _sd.latticeWidth).p.y << ")" */
  /*               << " "; */
  /*   } */
  /*   std::cout << std::endl; */
  /* } */
  /* auto i = 128; */
  /* auto j = 128; */
  /* std::cout << "v.at(i * _sd.latticeWidth + j).x= " */
  /*           << v.at(i * _sd.latticeWidth + j).p.x << std::endl; */
  /* std::cout << "v.at(i * _sd.latticeWidth + j).y= " */
  /*           << v.at(i * _sd.latticeWidth + j).p.y << std::endl; */
}

APath AStar::getPath(glm::vec2 s, glm::vec2 e)
{
  s.x += _sd.xOffset;
  s.y += _sd.yOffset;
  e.x += _sd.xOffset;
  e.y += _sd.yOffset;
  auto result = APath();

  /* std::cout << "_sd.xStep= " << _sd.xStep << std::endl; */
  /* std::cout << "_sd.yStep= " << _sd.yStep << std::endl; */
  unsigned int sxi = s.x / _sd.xStep;
  unsigned int syi = s.y / _sd.yStep;
  auto start = std::make_shared<ANode>(s, APoint{ sxi, syi });
  unsigned int exi = e.x / _sd.xStep;
  unsigned int eyi = e.y / _sd.yStep;
  auto end = std::make_shared<ANode>(e, APoint{ exi, eyi });
  start->g = 0;
  /* start->h = h(start->p, end->p); */
  start->f = start->g + h(start->p, end->p);

  std::set<std::shared_ptr<ANode>> frontier;
  frontier.emplace(start);
  std::set<std::shared_ptr<ANode>> closed;
  /* std::map<ANode*, float> gScore; */
  /* gScore.emplace(start.get(), 0); */
  /* std::map<ANode*, float> fScore; */
  /* fScore.emplace(start.get(), h(start->p, end->p)); */
  /* std::cout << "fScore.size()= " << fScore.size() << std::endl; */
  /* std::cout << "fScore[&start]= " << fScore[start.get()] << std::endl; */
  /* std::map<ANode*, ANode*> cameFrom; */
  std::cout << "sta position: (" << start->integerP.x << ", "
            << start->integerP.y << ")" << std::endl;
  std::cout << "end position: (" << end->integerP.x << ", " << end->integerP.y
            << ")" << std::endl;

  auto iterations = 0;
  while (!frontier.empty()) {
    /* std::cout << std::endl; */
    /* std::cout << "iteration= " << iterations++ << std::endl; */
    auto currentIt = std::min_element(
      frontier.begin(),
      frontier.end(),
      [](std::shared_ptr<ANode> lhs, std::shared_ptr<ANode> rhs) {
        return lhs->f < rhs->f;
      });
    auto current = *currentIt;

    /* std::cout << "curI position: (" << current->integerP.x << ", " */
    /*           << current->integerP.y << ")" << std::endl; */
    /* std::cout << "curF position: (" << cur->p.x << ", " << curt->p.y */
    /*           << ")" << std::endl; */
    /* std::cout << "endF position: (" << end.p.x << ", " << end.p.y << ")" */
    /*           << std::endl; */

    /* std::cout << "fScore[cur]= " << fScore[current.get()] << std::endl; */
    if (current->integerP == end->integerP) {
      return reconstructPath(current.get());
    }

    closed.insert(current);
    frontier.erase(currentIt);
    auto neighbors = getNeighbors(current.get());
    /* std::cout << "neighbors.size()= " << neighbors.size() << std::endl; */
    for (auto& n : neighbors) {
      /* std::cout << "processing neighbor= " << &n << std::endl; */
      /* auto tmp = current->g + _sd.xStep; */
      auto tmp = current->g + 0.01;
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
      fIt = std::find_if(
        frontier.begin(), frontier.end(), [&n](std::shared_ptr<ANode> node) {
          return (node->integerP == n.integerP);
        });
      cIt = std::find_if(
        closed.begin(), closed.end(), [&n](std::shared_ptr<ANode> node) {
          return (node->integerP == n.integerP);
        });
      if (fIt == frontier.end() && cIt == closed.end()) {
        auto a = std::make_shared<ANode>(n);
        a->g = tmp;
        a->f = tmp + h(a->p, end->p);
        a->parent = current.get();
        /* std::cout << "a.get()= " << a.get() << std::endl; */
        frontier.insert(a);
      }
      /* std::cout << "&n= " << &n << std::endl; */
      /* std::cout << "n.integerP.x= " << n.integerP.x << std::endl; */
      /* std::cout << "n.integerP.y= " << n.integerP.y << std::endl; */

      /* std::cout << "tmp= " << tmp << std::endl; */
      /* std::cout << "gScore[&n]= " << gScore[n.get()] << std::endl; */
      /* if (tmp < gScore[n.get()]) { */
      /* cameFrom.emplace(n.get(), current.get()); */
      /* gScore[n.get()] = tmp; */
      /* std::cout << "h(n.p, end.p)= " << h(n->p, end.p) << std::endl; */
      /* fScore[n.get()] = gScore[n.get()] + h(n->p, end.p); */
      /* if (frontier.find(n) == frontier.end()) { */
      /* std::cout << "add to frontier" << std::endl; */
      /* frontier.emplace(n); */
      /* } */
      /* } */
    }
    /* std::cout << "end of neighbors cycle" << std::endl; */
  }

  std::cout << "FAILURE of ASTAR" << std::endl;
  return APath();
}

float AStar::h(glm::vec2 c, glm::vec2 goal)
{
  return glm::distance(c, goal);
}

APath AStar::reconstructPath(ANode* current)
{
  /* std::cout << "reconstructPath" << std::endl; */
  auto path = APath();
  /* std::cout << "current= " << current << std::endl; */
  while (current->parent != nullptr) {
    auto p = glm::vec2(current->p.x - _sd.xOffset, current->p.y - _sd.yOffset);
    path.push_back(p);
    current = current->parent;
    /* std::cout << "cycle current= " << current << std::endl; */
  }

  /* std::cout << "path.size()= " << path.size() << std::endl; */
  return path;
}

bool operator==(const APoint& lhs, const APoint& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::vector<ANode> AStar::getNeighbors(const ANode* const current)
{
  /* std::cout << "_sd.latticeWidth= " << _sd.latticeWidth << std::endl; */
  auto cx = current->integerP.x;
  auto cy = current->integerP.y;
  struct Offset
  {
    int x;
    int y;
  };
  std::vector<Offset> offsets = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
  std::vector<ANode> res;
  for (auto& offset : offsets) {

    /* std::cout << "cx= " << cx << std::endl; */
    /* std::cout << "cy= " << cy << std::endl; */
    unsigned int i = cx + offset.x;
    unsigned int j = cy + offset.y;
    /* std::cout << "i= " << i << std::endl; */
    /* std::cout << "j= " << j << std::endl; */
    if (!_o.at(i * _sd.latticeWidth + j)) {
      float x = _v.at(i * _sd.latticeWidth + j).p.x;
      float y = _v.at(i * _sd.latticeWidth + j).p.y;
      /* std::cout << "x= " << x << std::endl; */
      /* std::cout << "y= " << y << std::endl; */
      /* ANode node = { glm::vec2(x, y), { i, j } }; */
      auto n = ANode(glm::vec2(x, y), APoint(i, j));
      res.push_back(n);
    }
  }
  return res;
}
