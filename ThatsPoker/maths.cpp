#include <maths.h>
#include <cmath>
#include <iostream>

float Maths::roundf(float x)
{
   return x >= 0.0f ? floorf(x + 0.5f) : ceilf(x - 0.5f);
}

float Maths::roundProba(float a_proba)
{
    return roundf(a_proba * 1000.f) / 1000.f;
}

double factorial(double nValue)
{
   double result = nValue;
   double result_next;
   double pc = nValue;

   while(pc > 2)
   {
       result_next = result*(pc-1);
       result = result_next;
       pc--;
   }

   return result;
}

double Maths::binomialCoeff(double nValue, double nValue2)
{
   double result;

   if(nValue2 == 1) return nValue;
   if(nValue == nValue2) return 1;

   double factorielNValue = factorial(nValue);
   double factorielNValue2 = factorial(nValue2);
   double factorielNValueMinusNValue2 = factorial(nValue - nValue2);

   result = factorielNValue / (factorielNValue2 * factorielNValueMinusNValue2);

   //std::cout << "[" << result << "] (" << factorielNValue << ") " << factorielNValue << " (" << nValue2 << ") " << factorielNValue2 << " (" << (nValue - nValue2) << ") " << factorielNValueMinusNValue2 << std::endl;


   return result;
}
