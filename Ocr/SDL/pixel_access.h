#ifndef PIXEL_ACCESS_H
#define PIXEL_ACCESS_H
#include <SDL2/SDL.h>

Uint8 *pixelref(SDL_Surface *surf, unsigned x, unsigned y);
Uint32 getpixel(SDL_Surface *img, unsigned int x, unsigned int y);
void putpixel(SDL_Surface *img, unsigned int x, unsigned int y, Uint32 pixel);

#endif
