#ifndef COLOR_HH_
#define COLOR_HH_

struct Color
{
  unsigned char	r;
  unsigned char	g;
  unsigned char	b;
  unsigned char	a;
  Color();
  Color(const Color &color);
  Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
  const Color &operator=(const Color &color);
  ~Color();
};

#endif // COLOR_HH_
