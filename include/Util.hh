#ifndef UTIL_HH_
#define UTIL_HH_

#include <math.h>

#define ALIGN (1.0)

class Point;

class Util
{
private:
  Util() = delete;
  Util(const Util &other) = delete;
  const Util &operator=(const Util &other) = delete;

public:
  static float quatCross(float a, float b, float c);
  static float f_rsqrt(float a);
  static float crossProduct(const Point &p1, const Point &p2, const Point &p3);
  static bool isFlatAngle(const Point &p1, const Point &p2, const Point &p3);
  static double round(double number, double increment = ALIGN, double offset = 0.0);
};

#include "Point.hh"

#endif // UTIL_HH_
