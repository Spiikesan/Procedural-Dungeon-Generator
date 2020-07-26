#ifndef GOBJECT_HH_
#define GOBJECT_HH_

struct GObject
{
  int index;
  GObject();
  GObject(const GObject &other);
  const GObject &operator=(const GObject &other);
  ~GObject();
};

#endif // GOBJECT_HH_
