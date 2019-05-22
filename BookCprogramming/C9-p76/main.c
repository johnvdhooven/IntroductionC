// If you find you use a sales tax rate that may change, use #define
// to set it in one place.

#include <stdio.h>

#define SALESTAX .07

int main()
{
   // Variables for the number of tires purchased, price,
   // a before-tax total, and a total cost with tax.
   int numTires;
   float tirePrice;
   float beforeTax;
   float netSales;

   /* Get the number of tires purchased and price per tire. */
   printf("How many tires did you purchase? ");
   scanf(" %d", &numTires);
   printf("What was the cost per tire (enter in $XX.XX format)? ");
   scanf(" $%f", &tirePrice);

   /* Compute the price. */
   beforeTax = tirePrice * numTires;
   netSales = beforeTax + (beforeTax * SALESTAX);
   printf("You spent $%.2f on your tires\n\n\n", netSales);

   return 0;
}