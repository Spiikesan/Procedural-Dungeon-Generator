#ifndef CIRCLE_HH_
#define CIRCLE_HH_

#include "GObject.hh"
#include "Point.hh"

struct Circle : GObject
{
  Point center;
  float radius;
  Circle();
  Circle(const Point &_center, float _radius);
  Circle(const Circle &other);
  const Circle &operator=(const Circle &other);
  bool isIn(const Point &pts) const;
  bool isAtRight(const Point &pts) const;
};

#endif // CIRCLE_HH_
