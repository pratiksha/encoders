#include <ctime>
#include <sys/types.h>
#include <unistd.h>

#include "random.h"

PRNG & Random::global_PRNG( void )
{
  static PRNG generator( time( NULL ) ^ getpid() );
  return generator;
}