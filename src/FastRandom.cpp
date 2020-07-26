#include <iostream>
#include "FastRandom.hh"

FastRandom::FastRandom()
    : m_currentState(0)
{
}

FastRandom::FastRandom(int seed)
    : m_currentState(seed)
{
}

FastRandom::FastRandom(unsigned int seed)
    : m_currentState(seed)
{
}

FastRandom::FastRandom(long seed)
    : m_currentState(((((unsigned long)seed & 0xFFFFFFFF00000000) >> 32) + 0x4a39b70d) * (((unsigned long)seed & 0xFFFFFFFF) + 0x12fad5c9))
{
}

FastRandom::FastRandom(unsigned long seed)
    : m_currentState((((seed & 0xFFFFFFFF00000000) >> 32) + 0x4a39b70d) * ((seed & 0xFFFFFFFF) + 0x12fad5c9))
{
}

FastRandom::FastRandom(int seedA, int seedB)
    : m_currentState((((unsigned int)seedA) + 0x4a39b70d) * (((unsigned int)seedB) + 0x12fad5c9))
{
}

double FastRandom::rndDouble(double min, double max)
{
  return ((double)next() / (double)(0xFFFFFFFF)) * (max - min) + min;
}

int FastRandom::rndInt(int min, int max)
{
  return (next() % (max - min)) + min;
}

unsigned int FastRandom::next()
{
  m_currentState += 0xe120fc15L;
  unsigned long tmp = (unsigned long)m_currentState * 0x4a39b70dL;
  unsigned int m1;
  m1 = (tmp >> 32) ^ tmp;
  tmp = (unsigned long)m1 * 0x12fad5c9L * m1;
  unsigned int m2 = (tmp >> 32) ^ tmp;
  return m2;
}
