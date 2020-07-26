#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <math.h>
#include "GObject.hh"
#include "Point.hh"
#include "Edge.hh"
#include "Circle.hh"

struct Triangle : GObject
{
  Point p1;
  Point p2;
  Point p3;
  Edge e1;
  Edge e2;
  Edge e3;
  Circle c;

  Triangle();
  Triangle(const Point &_p1, const Point &_p2, const Point &_p3);
  Triangle(const Triangle &other);
  ~Triangle();
  const Triangle &operator=(const Triangle &other);
  bool isCW() const;
  bool isCCW() const;
  Point getCenter() const;
  float getArea() const;
  Point getCircumCenter() const;
  float getCircumRadius() const;
  bool inCircumCircle(const Point &pts) const;
  bool isAtRightCircumCircle(const Point &pts) const;
};

std::ostream &operator<<(std::ostream &os, const Triangle &other);

#endif // TRIANGLE_H_
