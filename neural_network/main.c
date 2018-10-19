#include "sigmoid.h"
#include "exclusive_or.h"
#include <stdio.h>
#include <math.h>
#include "back_propagation.h"

int main()
{
  //printf("sigmoid(%f) = %f\n", (double) 3, sigmoid((double) 3));
  float in[2] = {1.0,1.0};
  float w1[4] = {0.475,0.175,0.275,0.775};
  float b1[2] = {0.4,0.5};
  float w2[4] = {0.45,0.65,0.75,0.35};
  float b2[2] = {0.1,0.8};
  float w3[2] = {0.37,0.1};
  float b3[1] = {0.7};
  float output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
  printf("exclusive_or(%f,%f) = %f\n", 1.0, 1.0, output);
  for (int i = 0; i < 400; i++)
    {
      back_prop_w(output, 0.0, w1, w2, w3);
      back_prop_b(output, 0.0, b1, b2, b3);
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) =%f\n", 1.0, 1.0, output);
    }
  printf("w1 = %f, %f, %f, %f\n w2 = %f, %f, %f, %f\n w3 = %f, %f\n b1 = %f, %f\n b2 = %f, %f\n  b3 = %f\n", w1[0], w1[1], w1[2], w1[3], w2[0], w2[1],w2[2], w2[3], w3[0], w3[1], b1[0], b1[1], b2[0], b2[1], b3[0]);   
  return 0;
}
