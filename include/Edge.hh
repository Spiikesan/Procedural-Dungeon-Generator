#ifndef _EDGE_HH_
#define _EDGE_HH_

#include "GObject.hh"
#include "Point.hh"

struct Edge : GObject
{
  Point p1;
  Point p2;

  Edge();
  Edge(const Edge &other);
  Edge(const Point &_p1, const Point &_p2);
  ~Edge();
  float length2() const;
  float length() const;
  static bool intersection(Point &outpts, const Edge &AB,
                           const Edge &CD);
  const Edge &operator=(const Edge &other);
  Point getCenter() const;
};

bool operator==(const Edge &a, const Edge &b);
bool operator!=(const Edge &a, const Edge &b);
bool operator>(const Edge &a, const Edge &b);
bool operator<(const Edge &a, const Edge &b);
bool operator>=(const Edge &a, const Edge &b);
bool operator<=(const Edge &a, const Edge &b);
std::ostream &operator<<(std::ostream &os, const Edge &edge);

#endif // _EDGE_HH__
