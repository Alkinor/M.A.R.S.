#ifndef BINARIZE_H
#define BINARIZE_H
#include <SDL2/SDL.h>

void greyscale(SDL_Surface *img);
void fillHisto(SDL_Surface *img, int *histo);
int findTreshold(int *histo);
void binarize(SDL_Surface *img);

#endif
