#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include <SDL2/SDL.h>
#include "matrix_content.h"

void redLine(SDL_Surface *img, int j);
void greenLine(SDL_Surface *img, int i); 
void lineDetect(SDL_Surface *img); 
void charDetect(SDL_Surface *img); 
SDL_Surface *detectChar(SDL_Surface *img); 
int delimitChar(SDL_Surface *img, int initialPoint, int currentWidth ); 
SDL_Surface *imgSection(SDL_Surface *img, int beginingH, int beginingW, int endH, int endW); 
Matrix convertIntoMatrix(SDL_Surface *img);
void resize(SDL_Surface *img, SDL_Surface *dest);
SDL_Surface *redimension(SDL_Surface *img, int newDImW, int newDimH);
int firstCharacter(SDL_Surface *img, int height);
int lastCharacter(SDL_Surface *img, int height);
int averageSpace(SDL_Surface *img, int beginnnig, int end, int height);
SDL_Surface *displayWords(SDL_Surface *img, int height, int heightMax);

#endif
