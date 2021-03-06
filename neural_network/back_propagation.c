#include "back_propagation.h"
#include "sigmoid.h"

void back_prop_w(float out, float ideal, float w1[], float w2[], float w3[])
{
  float error = (ideal - out);
  float eta = 0.2;
  float temp3[2];
  for (int i = 0; i < 2; i++)
    {
      temp3[i] = w3[i];
    }
  for (int i = 0; i < 2; i++)
    {
      temp3[i] +=  error * eta * sigmoid(-error * w3[i]); 
    }
  float temp2[4];
  for (int i = 0; i < 2; i++)
    {
      temp2[i] =w2[i];
    }
  for (int i = 0; i < 4; i++)
    {
      temp2[i] += (w3[i % 2] - temp3[i % 2]) * eta * derivative_sig(-(w3[i % 2] - temp3[i % 2]) * w2[i]);
    }
  for (int i = 0; i < 2; i++)
    {
      w3[i] = temp3[i];
    }
  for (int i = 0; i < 4; i++)
    {
      w1[i] += (w2[i/2] + w2[i/2+2] -temp2[i/2] - temp2[i/2+2])/2 * eta * derivative_sig(-(w2[i/2] + w2[i/2+2] -temp2[i/2] - temp2[i/2+2])/2 * w1[i]);
    }
  for (int i = 0; i < 4; i++)
    {
      w2[i] = temp2[i];
    }
}

void back_prop_b (float out, float ideal, float b1[], float b2[], float b3[])
{
  float eta = 1;
  float temp3 = 0.2;
  float temp2;
  for (int i = 0; i < 2; i++)
    {
      if (i < 1)
	{
	  temp3 = eta * (ideal - out) * sigmoid(-(ideal - out) * b3[i]);
	}
      temp2 = eta * temp3 * sigmoid(-temp3 * b2[i]);
      b3[0] += temp3;
      b1[i] += eta * (temp2) * sigmoid(-temp2 * b1[i]);
      b2[i] += temp2;
    }
}
