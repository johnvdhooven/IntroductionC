/* PRNG Pseudo-Random Number generator */

#include "prng.h"

#include <stdio.h>

#define N_RND 5

int main(void)
{
   unsigned long int seed = 123;
   int rnd = 0;

   printf("INFO: prng() returns a value in the range [0,%ld]\n", PRNG_MAX);

   printf("\n-- seed = 1 (default value)\n");
   for (int count = 0; count < N_RND; count++)
   {
      rnd = prng();
      printf("rnd = %d\n", rnd);
   }

   setSeed(seed);
   printf("\n-- seed = %lu\n", seed);

   for (int count = 0; count < N_RND; count++)
   {
      rnd = prng();
      printf("rnd = %d\n", rnd);
   }

   return 0;
}
