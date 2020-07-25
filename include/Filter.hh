#ifndef FILTER_HH_
# define FILTER_HH_

#include <vector>
#include <list>
#include <algorithm>
#include "Point.hh"
#include "Square.hh"
#include "Edge.hh"
#include "Triangle.hh"

struct Node
{
  Point pts;
  Edge  edge;
  float value;
  Node();
  Node(const Point &_pts, const Edge &_edge, float _value);
  Node (const Node &other);
  const Node &operator=(const Node &other);
  bool	operator<(const Node &other);
  bool	operator==(const Node &other);
};

class Filter
{
private:
  Filter() = delete;
  ~Filter() = delete;
  Filter(const Filter &other) = delete;
  const Filter &operator=(const Filter &other) = delete;
public:
  static const Point &getMin(const std::vector<Point> &tab);
  static const Point &getMax(const std::vector<Point> &tab);
  static std::vector<Square> getMoreOrEqualSize(const std::vector<Square> &square,
    float width, float height);
  static std::vector<Point> getCenterSquares(const std::vector<Square> &square);
  static std::vector<Edge> getAllEdges(const std::vector<Triangle> &triangles);
  template<class T>
  static void	depup(std::vector<T> &tab);
  static std::vector<Edge> getAllEdgesFromVertices(const std::vector<Edge> &edges,
      const Point &pts);
  static std::vector<Edge> getEdgesNotIn(const std::vector<Edge> &edges, const std::vector<Point> &pts);
  static std::vector<Edge> getEdgesNotIn(const std::vector<Edge> &edges, const std::vector<Edge> &others);
  static const Edge &getMin(const std::vector<Edge> &edges);
  static std::vector<Edge> getMininumSpanningTree(const std::vector<Edge> &edges,
    const std::vector<Point> &vertices);
  static std::vector<Edge> getPath(const std::vector<Edge> &edges, const std::vector<Square> &rooms);
  static std::vector<Square> cleanRoom(const std::vector<Edge> &edges, const std::vector<Square> &rooms);
  static std::vector<Square> addCorridor(const std::vector<Edge> &edges, const std::vector<Square> &rooms, float width);
};

#define FILTER_CPP
#include "../src/Filter.cpp"

#endif // FILTER_HH_
