#include "Color.hh"

Color::Color()
: r(0), g(0), b(0), a(0)
{

}

Color::Color(const Color &color)
: r(color.r), g(color.g), b(color.b), a(color.a)
{

}

Color::Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
: r(_r), g(_g), b(_b), a(_a)
{

}

const Color &Color::operator=(const Color &color)
{
    if (this != &color)
    {
      r = color.r;
      g = color.g;
      b = color.b;
      a = color.a;
    }
    return (*this);
}

Color::~Color()
{

}
