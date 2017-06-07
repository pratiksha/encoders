#ifndef _RANDOM__
#define _RANDOM__

#include <random>

typedef std::default_random_engine PRNG;

namespace Random {
  extern PRNG & global_PRNG();
}

#endif