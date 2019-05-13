#include <math.h>
#include <stdio.h>

#define EPSILON 1e-8

int fequal(double a, double b);

int main(void)
{
   double d1 = 0.1;
   double d2 = 0.2;
   float f1 = 0.1;

   printf("d1      = %.17lf\n", d1);
   printf("f1      = %.17f\n", f1);
   printf("d2      = %.17lf\n", d2);
   printf("d1 + d2 = %.17lf\n\n", d1 + d2);

   if (d1 == f1)
   {
      printf("double 0.1 == float 0.1\n");
   }
   else
   {
      printf("double 0.1 != float 0.1\n");
   }
   printf("\n");

   if (d1 + d2 == 0.3)
   {
      printf("0.1 + 0.2 == 0.3\n");
   }
   else
   {
      printf("0.1 + 0.2 != 0.3\n");
   }
   printf("\n");

   if (fequal(d1 + d2, 0.3))
   {
      printf("0.1 + 0.2 == 0.3\n");
   }
   else
   {
      printf("0.1 + 0.2 != 0.3\n");
   }
   printf("\n");

   return 0;
}

int fequal(double a, double b)
{
   return fabs(a-b) < EPSILON;
}
