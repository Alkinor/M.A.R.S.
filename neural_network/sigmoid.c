#include "exclusive_or.h"
#include <math.h>

double sigmoid(double x)
{
  return 1/(1+ exp(-x));
}

double derivative_sig(double x)
{
  return (exp(-x)) / ((1+exp(-x)) * (1+exp(-x)));
}

