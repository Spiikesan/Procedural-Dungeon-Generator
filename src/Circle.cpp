#include "Circle.hh"

Circle::Circle()
: GObject(), center(), radius(0)
{

}

Circle::Circle(const Point &_center, float _radius)
: GObject(), center(_center), radius(_radius)
{

}

Circle::Circle(const Circle &other)
: GObject(other), center(other.center), radius(other.radius)
{

}

const Circle &Circle::operator=(const Circle &other)
{
  if (this != &other)
  {
    GObject::operator=(other);
    center = other.center;
    radius = other.radius;
  }
  return (*this);
}

bool Circle::isIn(const Point &pts) const
{
  return ((pts - center).length2() <= (radius * radius));
}

bool Circle::isAtRight(const Point &pts) const
{
  Point tmp(pts - center);
  return (tmp.x * tmp.x > radius * radius);
}
