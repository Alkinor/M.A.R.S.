
#include <SDL2/SDL.h>
#include "pixel_access.h"
#include "SDL_content.h"
#include <stdio.h>
#include "matrix_content.h"

//Color a line in red

void redLine(SDL_Surface *img, unsigned int j)
{
  for (int i = 0; i < img->w; i++)
    {
      putpixel(img, i, j, SDL_MapRGB(img->format, 255, 0, 0));
    }
}

//Color a column in green from a position j to a position k

void greenLine(SDL_Surface *img, unsigned int i, unsigned int j, unsigned int k)
{
  for (unsigned int l = j; l < k; l++)
    {
      putpixel(img, i, l, SDL_MapRGB(img->format, 0, 255, 0));
    }
}

/*Color every line filled with white pixel in red
to separate all the lines of the text*/

void lineDetect(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int checked = 0;
  redLine(img, 0);
  for (int i = 0; i < img->w; i++)
    {
      for (int j = 1; j < img->h; j++)
	{
	  pixel = getpixel(img, j, i);
	  SDL_GetRGB(pixel,img->format, &r,&g,&b);
	  if ((r == 0) && (g == 0) && (b == 0))
	    {
	      checked = 1;
	      break;
	    }
	}
      if (checked == 0)
	{
	  redLine(img,i);
	}
      checked = 0;
    }
}

/*Color every columns filled with white pixel in green
from a red line to another */

void charDetect(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int pass = 1, start_cut = 1;
  int begining = 0, end = 0;

  for(int i = 0; i < img -> w; i++)
    {
      for (int j = 0; j < img->h; j++)
	{
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  if((r == 255) && (g == 255) && (b == 255) && (start_cut == 1))
	    {
	      start_cut = 0;
	      begining = j;
	      end = j;
	    }
	  if((r == 0) && (g == 0) && (b == 0) && (pass == 1))
	    {
	      pass = 0;
	      begining = 0;
	      end = 0;
	    }
	  if((r == 255) && (g == 0) & (b == 0) && (start_cut == 0))
	    {
	      greenLine(img, i, begining, end);
	      start_cut = 1;
	      pass = 1;
	    }
	  if((r == 255) && (g == 0) & (b == 0) && (start_cut == 0) && (pass == 1))
	    {
	      pass = 1;
	    }
	  if((r == 255) && (g == 255) && (b == 255) && (start_cut == 0) && (pass == 1))
	    {
	      end += 1;
	    }
	}
    }
}

//Return a portion of img of length ((endW - beginningW), (endH - beginningH)) 

SDL_Surface *imgSection(SDL_Surface *img, int beginningW, int beginningH, int endW, int endH)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int k = beginningW;
  int l = beginningH;
  SDL_Surface *character = SDL_CreateRGBSurface(0, endW - beginningW, endH - beginningH, 32, 0, 0, 0, 0);
  for(int i = 0; i < character->w; i++)
    {
      for(int j = 0; j < character->h; j++)
	{
	  pixel = getpixel(img, i + beginningW, j + beginningH);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  putpixel(character, i, j , SDL_MapRGB(img->format, r, g, b));
	  l += 1;
	}
      k += 1;
    }
  return character;
}

/*The 4 next functions are here to allow us
to cut the image into words of the text*/

//Find the first character of the image.

int firstCharacter(SDL_Surface *img, int height)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int first = 0;
  for (int i = 0; i < img->w; i++)
    {
      pixel = getpixel(img, i, height);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      if ((r == 0) && (g == 0) && (b == 0))
	{
	  first = i;
	  break;
	}
      if ((r == 255) && (g == 255) && (b == 255))
	{
	  first = i;
	  break;
	}
    }
  return first;
}

//Find the last character of the image.

int lastCharacter(SDL_Surface *img, int height)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int last = 0;
  for (int i = 1; i < img->w; i++)
    {
      pixel = getpixel(img, i, height);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      if ((r == 0) && (g == 255) && (b == 0))
	{
	  pixel = getpixel(img, i-1, height);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  if ((r == 0) && (g == 0) && (b == 0))
	    {
	      last = i;;
	    }
	  if ((r == 255) && (g == 255) && (b == 255))
	    {
	      last = i;
	    }
	}
    }
  return last;
}

/*Find the average space of the line.
We will then compare this value to a space width
If the space width is greater than the average, then it is
a space between two words. Else it is a space between
two characters.*/

int averageSpace(SDL_Surface *img, int beginning, int end, int height)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int spaceCount = 0;
  int widthSpaceCount = 0;
  int isCounting = 1;
  for (int i = beginning; i < end; i++)
    {
      pixel = getpixel(img, i, height);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      if ((r == 0) && (g == 255) && (b == 0) && (isCounting == 1))
	{
	  isCounting = 0;
	  spaceCount +=1;
	  widthSpaceCount += 1;
	}
      if ((r == 0) && (g == 255) && (b == 0) && (isCounting == 0))
	{
	  widthSpaceCount += 1;
	}
      if ((r == 0) && (g == 0) && (b == 0) && (isCounting == 0))
	{
	  isCounting = 1;
	}
      if ((r == 255) && (g == 255) && (b == 255) && (isCounting == 0))
	{
	  isCounting = 1;
	}
    }
  return widthSpaceCount/spaceCount;
}

/*Search words of the line between the first
character of the line to the last*/

SDL_Surface *displayWords(SDL_Surface *img, int height, int heightMax)
{
  Uint32 pixel;
  Uint8 r, g, b;
  SDL_Surface *word;
  int i = firstCharacter(img, height);
  int j = lastCharacter(img, height);
  int k = averageSpace(img, i, j, height);
  int beginning = i, end = i;
  int spaceCount = 0, start_count = 1;
  for (int l = i; l < j; l++)
    {
      pixel = getpixel(img, l, height);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      if ((r == 0) && (g == 255) && (b == 0) && (start_count == 0))
	{
	  spaceCount += 1;
	  end +=1;
	}
      if ((r == 0) && (g == 255) && (b == 0) && (start_count == 1))
	{
	  start_count = 0;
	  spaceCount += 1;
	  end += 1;
	}
      if ((r == 255) && (g == 255) && (b == 255) && (start_count == 0))
	{
	  if(spaceCount > k)
	    {
	      word = imgSection(img, beginning, height, end - spaceCount, heightMax);
	      break;
	    }
	  start_count = 1;
	  spaceCount = 0;
	}
      if ((r == 0) && (g == 0) && (b == 0) && (start_count == 0))
	{
	  if(spaceCount > k)
	    {
	      word = imgSection(img, beginning, height, end - spaceCount, heightMax);
	      break;
	    }
	  start_count = 0;
	  spaceCount = 0;
	}
      if ((r == 255) && (g == 255) && (b == 255) && (start_count == 1))
	{
	  end += 1;
	}
      if ((r == 0) && (g == 0) && (b == 0) && (start_count == 1))
	{
	  end += 1;
	}
    }
  return word;
}

/*Convert an image filled of black and white
into a matrix of 1 and 0.
1 corresponds to a black pixel.
0 corresponds to a white pixel*/

Matrix convertIntoMatrix(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r, g, b;
  Matrix matrix = newMatrix(img->h, img->w);
  initMatrix(matrix);
  for(int i = 0; i < img->w; i++)
    {
      for(int j = 0; j < img->h; j++)
	{
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  if ((r == 0) && (g == 0) && (b == 0))
	    {
	      matrix.matrix[i + j * matrix.y] = 1;
	    }
	}
    }
  return matrix;
}

//Copy the image into the destination

void resize(SDL_Surface *img, SDL_Surface *dest)
{
  double rx, ry;
  rx = dest->w*1.0/img->w; //We compute the ratio of the width and weight between the new image
  ry = dest->h*1.0/img->h; //and the old one
  Uint32 pixel;
  Uint8 r, g, b;
  for(int i = 0; i < dest->w; i++)
    {
      for(int j = 0; j < dest->h; j++)
	{
	  pixel = getpixel(img, i/rx, j/ry);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  putpixel(dest, i, j, SDL_MapRGB(img->format, r, g, b));
	}
    }
}

/*Create a new empty image and call a function to copy an image
into the empty one, but with new dimensions.
This will be usefull for the neural network*/

SDL_Surface *redimension(SDL_Surface *img, int newDimW, int newDimH)
{
  SDL_Surface *redimensionned = SDL_CreateRGBSurface(SDL_SWSURFACE, newDimW, newDimH, 32, 0, 0, 0, 0);
  resize(img, redimensionned);
  return redimensionned;
}

//Find the height's length of the character we want to extract from the image

int delimitChar(SDL_Surface *img, int initialPoint, int currentWidth)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int j = initialPoint;
  for (int i = initialPoint; i < img->h; i++)
    {
      pixel = getpixel(img, currentWidth, i);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      if((r == 255) && (g == 0) && (b == 0))
	{
	  break;
	}
      j += 1;
    }
  
  return j;
}

/*void detectChar(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int beginningW = 0, beginningH = 0;
  int endW = 0, endH = 0;
  int first = 0, cutting = 1;
  for(int i = 0; i < img->h; i++)
    {
      for(int j = 0; j < img->w; j++)
	{
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img -> format, &r, &g, &b);
	  if(((r == 0) && (g == 0) && (b == 0)) || ((r == 255) && (g == 255) & (b == 255)))
	    {
	      if(cutting == 1)
		{
		  printf("passed");
		  if (first == 0)
		    {
		      beginningW = j;
		      beginningH = i;
		      endW = j;
		      first = 1;
		      cutting = 0;
		      printf("%i\n", beginningW);
		    }
		  else
		    {
		      beginningW = j;;
		      endW = j;
		      cutting = 0;
		    }
		}
	    }
	  if(((r == 0) & (g == 0) & (b == 0)) || ((r == 255) & (g == 255) & (b == 255)))
	    {
	      if(cutting == 0)
		{
		  endW += 1;
		  }
	    }
	  if((r == 0) & (g == 255) & (b == 0) & (cutting == 1))
	    {
	      printf("A\n");
	      if(first)
		{
		  endH = delimit_char(img, i, j);
		}
	    }
	  if((r == 0) && (g == 0) && (b == 0))
	    {
	      printf("stop here\n");
	      break;
	    }
	}
    }
}*/


