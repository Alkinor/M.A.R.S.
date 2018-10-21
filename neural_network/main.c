#include "sigmoid.h"
#include "exclusive_or.h"
#include <stdio.h>
#include <math.h>
#include "back_propagation.h"
#include <stdlib.h>
#include <time.h>

int main()
{
  srand(time(NULL));
  //printf("sigmoid(%f) = %f\n", (double) 3, sigmoid((double) 3));
  float in[2] = {1.0,1.0};
  float w1[4] = {rand() / (float) RAND_MAX,rand() / (float) RAND_MAX,rand() / (float) RAND_MAX,rand() / (float) RAND_MAX};
  float b1[2] = {rand() / (float) RAND_MAX,rand() / (float) RAND_MAX};
  float w2[4] = {rand() / (float) RAND_MAX,rand() / (float) RAND_MAX,rand() / (float) RAND_MAX,rand() / (float) RAND_MAX};
  float b2[2] = {rand() / (float) RAND_MAX,rand() / (float) RAND_MAX};
  float w3[2] = {rand() / (float) RAND_MAX,rand() / (float) RAND_MAX};
  float b3[1] = {rand() / (float) RAND_MAX};
  float output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
  printf("exclusive_or(%f,%f) = %f\n", 1.0, 1.0, output);
  in[0] = 1;
  in[1] = 0;
  output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
  printf("exclusive_or(%f,%f) = %f\n", 1.0, 0.0, output);
  in[0] = 0;
  in[1] = 0;
  output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
  printf("exclusive_or(%f,%f) = %f\n", 0.0, 0.0, output);
  in[0] = 0;
  in[1] = 1;
  output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
  printf("exclusive_or(%f,%f) = %f\n", 0.0, 1.0, output);
  in[0] = 1;
  in[1] = 1;
  for (int i = 0; i < 100; i++)
    {
      for (int j = 0; j < 10; j++)
	{
	  back_prop_w(output, 0.0, w1, w2, w3);
	  back_prop_b(output, 0.0, b1, b2, b3);
	  output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
	}
      printf("1 1 learned\n");
      in[0] = 1;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 1.0, 1.0, output);
      in[0] = 1;
      in[1] = 0;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 1.0, 0.0, output);
      in[0] = 0;
      in[1] = 0;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 0.0, 0.0, output);
      in[0] = 0;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 0.0, 1.0, output);
      in[0] = 1;
      in[1] = 0;
      for (int j = 0; j < 10; j++)
	{
	  output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
	  back_prop_w(output, 1.0, w1, w2, w3);
	  back_prop_b(output, 1.0, b1, b2, b3);
	}
      printf("1 0 learned\n");
      in[0] = 1;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 1.0, 1.0, output);
      in[0] = 1;
      in[1] = 0;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 1.0, 0.0, output);
      in[0] = 0;
      in[1] = 0;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 0.0, 0.0, output);
      in[0] = 0;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 0.0, 1.0, output);
      in[0] = 0;
      in[1] = 0;
      for (int j = 0; j < 10; j++)
	{
	  output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
	  back_prop_w(output, 0.0, w1, w2, w3);
	  back_prop_b(output, 0.0, b1, b2, b3);
	}
      printf("0 0 learned\n");
      in[0] = 1;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 1.0, 1.0, output);
      in[0] = 1;
      in[1] = 0;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 1.0, 0.0, output);
      in[0] = 0;
      in[1] = 0;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 0.0, 0.0, output);
      in[0] = 0;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 0.0, 1.0, output);
      in[0] = 0;
      in[1] = 1;
      for (int j = 0; j < 10; j++)
	{
	  output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
	  back_prop_w(output, 1.0, w1, w2, w3);
	  back_prop_b(output, 1.0, b1, b2, b3);
	}
      printf("0 1 learned\n");
      in[0] = 1;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 1.0, 1.0, output);
      in[0] = 1;
      in[1] = 0;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 1.0, 0.0, output);
      in[0] = 0;
      in[1] = 0;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 0.0, 0.0, output);
      in[0] = 0;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
      printf("exclusive_or(%f,%f) = %f\n", 0.0, 1.0, output);
      in[0] = 1;
      in[1] = 1;
      output = exclusive_or(in,w1,b1,w2,b2,w3,b3);
    }
  printf("w1 = %f, %f, %f, %f\n w2 = %f, %f, %f, %f\n w3 = %f, %f\n b1 = %f, %f\n b2 = %f, %f\n  b3 = %f\n", w1[0], w1[1], w1[2], w1[3], w2[0], w2[1],w2[2], w2[3], w3[0], w3[1], b1[0], b1[1], b2[0], b2[1], b3[0]);   
  return 0;
}
