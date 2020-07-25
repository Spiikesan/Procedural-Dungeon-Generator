#include "Util.hh"

float Util::quatCross(float a, float b, float c)
{
  return (sqrt((a + b + c) * (a + b - c) * (a - b + c) * (-a + b + c)));
}

float Util::f_rsqrt(float number)
{
  union u_u
  {
      long	i;
      double	y;
  } u;

  float x2;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  u.y  = number;
  u.i  = 0x5fe6ec85e7de30da - ( u.i >> 1 ); // what the fuck?
  return (u.y * ( threehalfs - (x2 * u.y * u.y ) ));
}

float Util::crossProduct(const Point &p1, const Point &p2, const Point &p3)
{
  Point P1P2 = p2 - p1;
  Point P2P3 = p3 - p2;
  return (P1P2.x * P2P3.y - P1P2.x * P2P3.y);
}

bool Util::isFlatAngle(const Point &p1, const Point &p2, const Point &p3)
{
  return (Util::crossProduct(p1, p2, p3));
}
