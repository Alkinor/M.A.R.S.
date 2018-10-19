#include "back_propagation.h"
#include "sigmoid.h"

void back_prop_w(float out, float ideal, float w1[], float w2[], float w3[])
{
  float error = (ideal - out);
  float eta = 10.0;
  float temp3[2];
  for (int i = 0; i < 2; i++)
    {
      temp3[i] = w3[i];
    }
  error = 1;
  for (int i = 0; i < 2; i++)
    {
      temp3[i] +=  error * eta * derivative_sig(w3[i]); 
    }
  float temp2[4];
  for (int i = 0; i < 2; i++)
    {
      temp2[i] =w2[i];
    }
  for (int i = 0; i < 4; i++)
    {
      temp2[i] += (w3[i % 2] - temp3[i % 2])  * eta * derivative_sig(w2[i]);
    }
  w3 = temp3;
  for (int i = 0; i < 4; i++)
    {
      w1[i] += (w2[i/2] + w2[i/2+2] -temp2[i/2] - temp2[i/2+2])/2  * eta * derivative_sig(w1[i]);
    }
  w2 = temp2;
}

void back_prop_b (float out, float ideal, float b1[], float b2[], float b3[])
{
  float eta = 10.0;
  for (int i = 0; i < 2; i++)
    {
      if (i < 1)
	{
	  b3[i] += eta * 1 * derivative_sig(b3[i]) * (ideal - out);
	}
      b2[i] += eta * 1 * derivative_sig(b2[i]) * (ideal - out);
      b1[i] += eta * 1 * derivative_sig(b1[i]) * (ideal - out);
    }
}
