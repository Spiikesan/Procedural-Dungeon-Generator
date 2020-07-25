#include "Triangle.hh"

Triangle::Triangle()
: GObject(), p1(), p2(), p3(), e1(p1, p2), e2(p2, p3), e3(p3, p1)
{
  c = Circle(getCircumCenter(), getCircumRadius());
}

Triangle::Triangle(const Point &_p1, const Point &_p2, const Point &_p3)
  : GObject(), p1(_p1), p2(_p2), p3(_p3), e1(p1, p2), e2(p2, p3), e3(p3, p1)
{
  c = Circle(getCircumCenter(), getCircumRadius());
}

Triangle::Triangle(const Triangle &other)
: GObject(other), p1(other.p1), p2(other.p2), p3(other.p3),
  e1(other.e1), e2(other.e2), e3(other.e3), c(other.c)
{

}

const Triangle &Triangle::operator=(const Triangle &other)
{
  if (this != &other)
  {
    GObject::operator=(other);
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    e1 = other.e1;
    e2 = other.e2;
    e3 = other.e3;
    c = other.c;
  }
  return (*this);
}

Triangle::~Triangle()
{

}

bool Triangle::isCW() const
{
  return (Util::crossProduct(p1, p2, p3) < 0);
}

bool Triangle::isCCW() const
{
  return (Util::crossProduct(p1, p2, p3) > 0);
}

Point Triangle::getCenter() const
{
  return ((p1 + p2 + p3) / 3.0);
}

float Triangle::getArea() const
{
  return (Util::quatCross(p1.length(), p2.length(), p3.length() / 4.0));
}

Point Triangle::getCircumCenter() const
{
  Point P3P2(p3.x - p2.x, p2.y - p3.y);
  Point P1P3(p1.x - p3.x, p3.y - p1.y);
  Point P2P1(p2.x - p1.x, p1.y - p2.y);
  float lenA2 = p1.length2();
  float lenB2 = p2.length2();
  float lenC2 = p3.length2();

  float D =  (p1.x * P3P2.y + p2.x * P1P3.y + p3.x * P2P1.y) * 2.0;
  float x = lenA2 * P3P2.y + lenB2 * P1P3.y + lenC2 * P2P1.y;
  float y = lenA2 * P3P2.x + lenB2 * P1P3.x + lenC2 * P2P1.x;
  return Point((x / D), (y / D));
}

float Triangle::getCircumRadius() const
{
  float lenA = e1.length();
  float lenB = e2.length();
  float lenC = e3.length();

  return (lenA * lenB * lenC) / Util::quatCross(lenA, lenB, lenC);
}

bool Triangle::inCircumCircle(const Point &pts) const
{
  return (c.isIn(pts));
}

bool Triangle::isAtRightCircumCircle(const Point &pts) const
{
  return (c.isAtRight(pts));
}

std::ostream &operator<<(std::ostream &os, const Triangle &other)
{
  os << "{(" << other.p1 << ")" << "; (" << other.p2 << "); (" << other.p3 << ")}";
  return (os);
}
