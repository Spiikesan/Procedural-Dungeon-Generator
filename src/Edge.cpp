#include "Edge.hh"

Edge::Edge()
    : p1(), p2()
{
}

Edge::Edge(const Edge &other)
    : GObject(), p1(other.p1), p2(other.p2)
{
}

Edge::Edge(const Point &_p1, const Point &_p2)
    : p1(_p1), p2(_p2)
{
}

Edge::~Edge()
{
}

const Edge &Edge::operator=(const Edge &other)
{
  if (this != &other)
  {
    GObject::operator=(other);
    p1 = other.p1;
    p2 = other.p2;
  }
  return (*this);
}

float Edge::length2() const
{
  return (Point::dist2(p1, p2));
}

float Edge::length() const
{
  return (sqrt(length2()));
}

bool Edge::intersection(Point &outpts, const Edge &AB,
                        const Edge &CD)
{
  Point lineVecBA(AB.p1 - CD.p1);
  Point crossVecAB(Point::cross(AB.p2, CD.p2));
  Point crossVecBAB(Point::cross(lineVecBA, CD.p2));

  float planarFactor = Point::dot(lineVecBA, crossVecAB);
  if (abs(planarFactor) < 0.0001f && crossVecAB.length() > 0.0001f)
  {
    float s = Point::dot(crossVecBAB, crossVecAB) / crossVecAB.length();
    outpts = AB.p1 + AB.p2 * s;
    return (true);
  }
  outpts = Point();
  return (false);
}

Point Edge::getCenter() const
{
  return (Point(p1.x + (p2.x - p1.x) / 2.0, p1.y + (p2.y - p1.y) / 2.0));
}

std::ostream &operator<<(std::ostream &os, const Edge &edge)
{
  os << "{(" << edge.p1 << "), (" << edge.p2 << ")}";
  return (os);
}

bool operator==(const Edge &a, const Edge &b)
{
  //std::cout << a << "==" << b << std::endl;
  return ((a.p1 == b.p1) && (a.p2 == b.p2)) || ((a.p1 == b.p2) && (a.p2 == b.p1));
}

bool operator!=(const Edge &a, const Edge &b)
{
  return (!(a == b));
}

bool operator>(const Edge &a, const Edge &b)
{
  float da = a.length2();
  float db = b.length2();
  return (da > db);
}

bool operator<(const Edge &a, const Edge &b)
{
  float da = a.length2();
  float db = b.length2();
  return (da < db);
}

bool operator>=(const Edge &a, const Edge &b)
{
  return (a == b || a > b);
}

bool operator<=(const Edge &a, const Edge &b)
{
  return (a == b || a < b);
}
