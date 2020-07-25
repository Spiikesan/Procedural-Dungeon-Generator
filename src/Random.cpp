#include "Random.hh"

Random::Random()
: _seed(0), _tmp(0)
{
}

Random::Random(unsigned int seed)
: _seed(seed), _tmp(seed)
{
}

Random::Random(const Random &other)
: _seed(other.getSeed()), _tmp(other._tmp)
{

}
const Random &Random::operator=(const Random &other)
{
  if (this != &other)
  {
    _seed = other.getSeed();
    _tmp = other._tmp;
  }
  return (*this);
}

Random::~Random()
{

}

float	Random::getFloat(float min, float max)
{
  return ((max-min)*((float)rand_r(&_tmp)/RAND_MAX))+min;
}

double 	Random::getDouble(double min, double max)
{
  return ((max-min)*((double)rand_r(&_tmp)/RAND_MAX))+min;
}

int 	Random::getInt(int min, int max)
{
  return (getFloat(min, max));
}

unsigned int	Random::getSeed() const
{
  return (_seed);
}

void		Random::reset()
{
  _tmp = _seed;
}

void	Random::setSeed(unsigned int value)
{
  if (_seed != value)
    {
      _seed = value;
      reset();
    }
}
