#include "GObject.hh"
#include <iostream>

GObject::GObject()
    : index(-1)
{
}

GObject::GObject(const GObject &other)
    : index(other.index)
{
}

const GObject &GObject::operator=(const GObject &other)
{
  if (this != &other)
  {
    index = other.index;
  }
  return (*this);
}

GObject::~GObject()
{
}
