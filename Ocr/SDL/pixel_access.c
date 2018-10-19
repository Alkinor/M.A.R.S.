#include <stdio.h>
#include <SDL2/SDL.h>

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

//Return the pixel at location x, y

Uint32 getpixel(SDL_Surface *surface, unsigned int x, unsigned int y)
{
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel)
    {
    case 1:
      return *p;
      break;
      
    case 2:
      return *(Uint16 *)p;
      break;
      
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
	 return p[0] << 16 | p[1] << 8 | p[2];
	}
      else
	{
	  return p[0] | p[1] << 8 | p[2] << 16;
	}
      break;
      
    case 4:
      return *(Uint32 *)p;
      break;
    }
  return 0;
}

//Replace a pixel at location x, y by another one

void putpixel(SDL_Surface *surface, unsigned int x, unsigned int y, Uint32 pixel)
{
  Uint8 *p = pixelref(surface, x, y);
  
  switch(surface->format->BytesPerPixel)
    {
    case 1:
      *p = pixel;
      break;
      
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
	  p[0] = (pixel >> 16) & 0xff;
	  p[1] = (pixel >> 8) & 0xff;
	  p[2] = pixel & 0xff;
	}
      else
	{
	  p[0] = pixel & 0xff;
	  p[1] = (pixel >> 8) & 0xff;
	  p[2] = (pixel >> 16) & 0xff;
	}
      break;
    case 4:
      *(Uint32 *)p = pixel;
      break;
    }
}
