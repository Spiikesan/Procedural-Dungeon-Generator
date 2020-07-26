#ifndef GENERATE_HH_
#define GENERATE_HH_

#include <Square.hh>
#include <Point.hh>
#include <Triangle.hh>
#include <Edge.hh>
#include <Filter.hh>

#include <cmath>
#include <vector>
#include <algorithm>
#include "FastRandom.hh"

class Generate
{
  static FastRandom rnd;

public:
  ~Generate() {}

  static void setSeed(unsigned int);
  static std::vector<Square> squares(const std::vector<Point> &pts, float min, float max);
  static std::vector<Point> pointsInCircle(size_t n, Point center, float width, float height);
  static std::vector<Point> pointsInSquare(size_t n, Point center, float width, float height);
  static Triangle superTriangle(std::vector<Point> const &v);
  static std::vector<Triangle> delaunay(const std::vector<Point> &vertices);
};

#endif // GENERATE_HH_
