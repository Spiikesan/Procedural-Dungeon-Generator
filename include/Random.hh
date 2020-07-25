#ifndef RANDOM_HH_
# define RANDOM_HH_

# include <cstdlib>

class Random
{
private:
  unsigned int _seed;
  unsigned int _tmp;
public:
  Random();
  Random(unsigned int seed);
  Random(const Random &other);
  const Random &operator=(const Random &other);
  ~Random();
  float		getFloat(float min, float max);
  double 	getDouble(double min, double max);
  int 		getInt(int min, int max);
  unsigned int	getSeed() const;
  void		reset();
  void		setSeed(unsigned int value);
};

#endif // RANDOM_HH_
