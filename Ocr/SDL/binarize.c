#include <stdio.h>
#include <SDL2/SDL.h>
#include "binarize.h"
#include "pixel_access.h"

//Turn the image to grey using a greyscale

void greyscale(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r, g, b, average;
    for (int i = 0; i < img->w; ++i)
    {
        for (int j = 0; j < img->h; ++j)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            average = (r + g + b) / 3;
	    putpixel(img, i, j, SDL_MapRGB(img->format, average, average, average));
        }
    }
}

//The three methods below are used to binarize the image by using Otsu's method

//Create an histogram with the number of occurencies of a grey value

void fillHisto(SDL_Surface *img, int *histo)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int k = 0;
  for(int i = 0; i < img->w; i++)
    {
      for(int j = 0; j < img->h; j++)
	{
	  pixel = getpixel(img, i, j);
          SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  histo[r] += 1;
	  k++;
	}
    }
}

/*Find the value used to determine if we should turn the grey
of the pixel to black or white*/

int findTreshold(int *histo)
{
  float sum1 = 0, sum2 = 0;
  float mean1 = 0, mean2 = 0;
  float isum1 = 0, isum2 = 0;
  float max = 0, new = 0;
  int threshold = 0;
  for (int i = 0; i < 128; i++)
    {
      sum1 += histo[i];
      sum2 += histo[256 - i];
      isum1 += i * histo[i];
      isum2 += (256 - i) * histo[256 - i];
      mean1 = isum1/sum1;
      mean2 = isum2/sum2;
      new = sum1 * sum2 * (mean1 - mean2) * (mean1 - mean2);
      if(new > max)
	{
	  max = new;
	  threshold = i;
	}
    }
  return threshold;
}

/*Binarize the image by comparing the pixel value to
the threshold found with findTreshold*/

void binarize(SDL_Surface *img)
{
  greyscale(img);
  Uint32 pixel;
  Uint8 r, g, b;
  int *histo = calloc(256, sizeof(int));
  fillHisto(img, histo);
  int threshold = findTreshold(histo);
  for(int i = 0; i < img -> w; i++)
    {
      for(int j = 0; j < img-> h; j++)
	{
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  if(r > threshold)
	    {
	      putpixel(img, i, j, SDL_MapRGB(img->format, 255, 255, 255));
	    }
	   else
	    {
	      putpixel(img, i, j, SDL_MapRGB(img->format, 0, 0, 0));
	    }
	}
    }
}
