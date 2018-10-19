#include "exclusive_or.h"
#include "sigmoid.h"

float exclusive_or(float in[], float w1[], float b1[], float w2[],float b2[], float w3[],float b3[])
{
  float layer_1_out[4];
  for (int i = 0; i < 2; i++)
    {
      float z_i = 0;
      for (int j = 0; j < 2; j++)
	{
	  z_i += w1[j + 2*i] * in[j];
	}
      layer_1_out[i] = sigmoid (z_i) + b1[i];
    }
  float layer_2_out[4];
  for (int i = 0; i < 2; i++)
    {
      float z_i = 0;
      for (int j = 0; j < 2; j++)
	{
	  z_i += w2[j + 2*i] * layer_1_out[j];
	}
      layer_2_out[i] = sigmoid (z_i) + b2[i];
    }
  float output = 0;
  for (int i = 0; i < 2; i++)
    {
      output += layer_2_out[i] * w3[i];
    }
  return sigmoid(output + b3[0]);
}
