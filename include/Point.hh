#ifndef _POINT_HH_
# define _POINT_HH_

#include <math.h>
#include <iostream>
#include <string>
#include "Util.hh"
#include "GObject.hh"

struct Point : GObject
{
  float	x;
  float	y;

  Point();
  Point (const Point &other);
  Point(float _x, float _y);
  ~Point();
  Point &normalize();
  float length() const;
  float length2() const;
  const Point &operator=(const Point &other);
  const Point &operator+=(const Point &other);
  const Point &operator+=(float other);
  const Point &operator-=(const Point &other);
  const Point &operator-=(float other);
  const Point &operator*=(const Point &other);
  const Point &operator*=(float other);
  const Point &operator/=(const Point &other);
  const Point &operator/=(float other);
  static const Point &max(const Point &a, const Point &b);
  static const Point &min(const Point &a, const Point &b);
  static Point cross(const Point &a, const Point &b);
  static float dot(const Point &a, const Point &b);
  static const Point &clamp (const Point &p, const Point &min, const Point &max);
  static float dist2(const Point &a, const Point &b);
  static float dist(const Point &a, const Point &b);
};

Point operator+(const Point &a, const Point &b);
Point operator+(const Point &a, float b);
Point operator-(const Point &a, const Point &b);
Point operator-(const Point &a, float b);
Point operator*(const Point &a, const Point &b);
Point operator*(const Point &a, float b);
Point operator/(const Point &a, const Point &b);
Point operator/(const Point &a, float b);
bool operator==(const Point &a, const Point &b);
bool operator!=(const Point &a, const Point &b);
bool operator>(const Point &a, const Point &b);
bool operator<(const Point &a, const Point &b);
bool operator>=(const Point &a, const Point &b);
bool operator<=(const Point &a, const Point &b);
std::ostream &operator<<(std::ostream &os, const Point &pts);

#endif // _POINT_HH_
