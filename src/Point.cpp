#include "Point.hh"

Point::Point()
    : GObject(), x(0.0), y(0.0)
{
}

Point::Point(const Point &other)
    : GObject(other), x(other.x), y(other.y)
{
}

Point::Point(float _x, float _y)
    : GObject(), x(_x), y(_y)
{
}

Point::~Point()
{
}

Point &Point::normalize()
{
  float inv_nor = Util::f_rsqrt(length2());
  if (inv_nor)
  {
    operator*=(inv_nor);
  }
  return (*this);
}

float Point::length() const
{
  return (fabs(x) + fabs(y));
}

float Point::length2() const
{
  return (x * x + y * y);
}

const Point &Point::max(const Point &a, const Point &b)
{
  return (a > b ? a : b);
}

const Point &Point::min(const Point &a, const Point &b)
{
  return (a < b ? a : b);
}

Point Point::cross(const Point &a, const Point &b)
{
  return (Point(a.x * b.x, -b.y * a.y));
}

float Point::dot(const Point &a, const Point &b)
{
  return ((a.x * b.x) + (a.y * b.y));
}

const Point &Point::clamp(const Point &p, const Point &min, const Point &max)
{
  return (Point::min(Point::max(p, min), max));
}

float Point::dist2(const Point &a, const Point &b)
{
  float abx = (a.x - b.x);
  float aby = (a.y - b.y);
  return abx * abx + aby * aby;
}

float Point::dist(const Point &a, const Point &b)
{
  return (sqrt(Point::dist2(a, b)));
}

const Point &Point::operator=(const Point &other)
{
  if (*this != other)
  {
    GObject::operator=(other);
    x = other.x;
    y = other.y;
  }
  return (*this);
}

const Point &Point::operator+=(const Point &other)
{
  x += other.x;
  y += other.y;
  return (*this);
}

const Point &Point::operator+=(float other)
{
  x += other;
  y += other;
  return (*this);
}

const Point &Point::operator-=(const Point &other)
{
  x -= other.x;
  y -= other.y;
  return (*this);
}

const Point &Point::operator-=(float other)
{
  x -= other;
  y -= other;
  return (*this);
}

const Point &Point::operator*=(const Point &other)
{
  x *= other.x;
  y *= other.y;
  return (*this);
}

const Point &Point::operator*=(float other)
{
  x *= other;
  y *= other;
  return (*this);
}

const Point &Point::operator/=(const Point &other)
{
  x /= other.x;
  y /= other.y;
  return (*this);
}

const Point &Point::operator/=(float other)
{
  x /= other;
  y /= other;
  return (*this);
}

Point operator+(const Point &a, const Point &b)
{
  Point r(a);
  return (r += b);
}

Point operator+(const Point &a, float b)
{
  Point r(a);
  return (r += b);
}

Point operator-(const Point &a, const Point &b)
{
  Point r(a);
  return (r -= b);
}

Point operator-(const Point &a, float b)
{
  Point r(a);
  return (r -= b);
}

Point operator*(const Point &a, const Point &b)
{
  Point r(a);
  return (r *= b);
}

Point operator*(const Point &a, float b)
{
  Point r(a);
  return (r *= b);
}

Point operator/(const Point &a, const Point &b)
{
  Point r(a);
  return (r /= b);
}

Point operator/(const Point &a, float b)
{
  Point r(a);
  return (r /= b);
}

bool operator==(const Point &a, const Point &b)
{
  return (a.x == b.x && a.y == b.y);
}

bool operator!=(const Point &a, const Point &b)
{
  return (!(a == b));
}

bool operator>(const Point &a, const Point &b)
{
  float da = a.length2();
  float db = b.length2();
  return (da > db);
}

bool operator<(const Point &a, const Point &b)
{
  float da = a.length2();
  float db = b.length2();
  return (da < db);
}

bool operator>=(const Point &a, const Point &b)
{
  return (a == b || a > b);
}

bool operator<=(const Point &a, const Point &b)
{
  return (a == b || a < b);
}

std::ostream &operator<<(std::ostream &os, const Point &pts)
{
  os << pts.x << ", " << pts.y;
  return (os);
}
