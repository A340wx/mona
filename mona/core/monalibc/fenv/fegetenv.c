#include <fenv.h>

int fegetenv(fenv_t *f)
{
  if( !f ) return -1;
  asm volatile("fstenv %0" : "=m"(*f));
  return 0;
}
