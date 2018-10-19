#ifndef SDL_CONTENT_H
#define SDL_CONTENT_H
#include <SDL2/SDL.h>

int init_SDL();
SDL_Surface *load_image(char *n);
void display_image();
void quit_SDL();

#endif
