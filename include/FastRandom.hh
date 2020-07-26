#pragma once
class FastRandom
{
public:
  FastRandom();
  FastRandom(int seed);
  FastRandom(unsigned int seed);
  FastRandom(long seed);
  FastRandom(unsigned long seed);
  FastRandom(int seedA, int seedB);

  double rndDouble(double min, double max);

  int rndInt(int min, int max);

  unsigned int next();

  unsigned int getCurrentState() const { return m_currentState; }

private:
  unsigned int m_currentState;
};
