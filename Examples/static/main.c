#include <stdio.h>

int f1(void);
int f2(void);
int addingup(int delta);

int main(void)
{
   int resetValue = 0;

   printf("\n f1()  %d ", f1());
   printf(" %d ", f1());
   printf(" %d ", f1());
   printf(" %d\n", f1());

   printf(" f2()  %d ", f2());
   printf(" %d ", f2());
   printf(" %d ", f2());
   printf(" %d\n\n", f2());

   printf(" addingup(2)  =%3d  ", addingup(2));
   printf(" addingup(5)  =%3d  ", addingup(5));
   printf(" addingup(-2) =%3d\n\n", addingup(-2));

   /* Reset addingup() */
   resetValue = addingup(0);
   addingup(-resetValue);
   printf(" addingup(0) returns value static int sum =%3d\n\n", addingup(0));

   return 0;
}

int f1(void)
{
   int i = 0; /* local variable created on the stack,
                 every time this function is called */
   i++;
   return i;
}

int f2(void)
{
   static int i = 0; /* static local variable created on the heap,
                        initial value: at first function call */
   i++;
   return i;
}

int addingup(int delta)
{
   static int sum = 0;
   sum += delta;
   return sum;
}
