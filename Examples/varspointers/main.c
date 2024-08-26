#include <stdio.h>

int main(void)
{
   int i1 = 0;
   int i2 = 1;
   int data[3] = {10, 20, 30};
   double d = 1.123;
   int *pInt = data;

   printf("\n"
          "int i1 = 0;\n"
          "int i2 = 1;\n"
          "int data[3] = {10, 20, 30};\n"
          "double d = 1.123;\n"
          "int *pInt = data;\n\n");

   printf("Information about i1\n");
   printf("%18s: %20s\n", "Definition", "int i1 = 0");
   printf("%18s: %20d\n", "Value data[0]", i1);
   printf("%18s: %20p\n\n", "Address data[0]", &i1);

   printf("Information about i2\n");
   printf("%18s: %20s\n", "Definition", "int i2 = 0");
   printf("%18s: %20d\n", "Value", i2);
   printf("%18s: %20p\n\n", "Address", &i2);

   printf("Information about data\n");
   printf("%18s: %20s\n", "Definition", "int data[3] = {10, 20, 30}");
   printf("%18s: %20p\n\n", "Address", data);

   printf("%18s: %20d\n", "Value [0]", data[0]);
   printf("%18s: %20p\n\n", "Address [0]", &data[0]);
   printf("%18s: %20d\n", "Value [1]", data[1]);
   printf("%18s: %20p\n\n", "Address [1]", &data[1]);
   printf("%18s: %20d\n", "Value [2]", data[2]);
   printf("%18s: %20p\n\n", "Address [2]", &data[2]);

   printf("%18s: %20p\n", "pointer[1] - pointer[0]", &data[1] - &data[0]);
   printf("%s", "Observe the difference in addresses is 4 (bytes)\n"
                "But the de difference in pointer arithmic is just 1\n"
                "Pointer arithmic is aware of the type and size of variables used\n"
                "\n");
   printf("Value of data[0] using data[0]: %d\n", data[0]);
   printf("Value of data[0] using *(&data[0]): %d\n", *(&data[0]));
   printf("Value of data[1] using *(&data[0] + 1): %d\n", *(&data[0] + 1));
   printf("%s", "Observe &data[0] results in the pointer to data[0]\n"
          "so using pointer arithmic &data[0] + 1 points to data[1]\n"
          "\n");

   printf("%s", "The use of *pInt = data\n"
          "*pInt = data results in a pointer to de the array data\n");
   printf("Value of data[0] using data[0]: %d\n", data[0]);
   printf("Value of data[0] using *pInt: %d\n", *pInt);
   printf("Value of data[1] using *(pInt + 1): %d\n", *(pInt + 1));
   printf("%s", "Observe pInt is the pointer to data[0]\n"
          "so using pointer arithmic *(pInt + 1) points to data[1]\n"
          "\n");
   printf("%s", "There is quite a difference between *(pInt + 1) and *pInt + 1!!!!!\n");
   printf("Value of *(pInt + 1): %d\t%s\n", *(pInt + 1), "//First add 1 to the pointer, then show value");
   printf("Value of *pInt + 1: %d\t%s\n", *pInt + 1, "//First get the value of data[0] and add 1 to this value");


   printf("Information about d\n");
   printf("%18s: %20s\n", "Definition", "double d = 1.123");
   printf("%18s: %20lf\n", "Value", d);
   printf("%18s: %20p\n\n", "Address", &d);







   return 0;
}


