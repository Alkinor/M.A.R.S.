#include <stdio.h>
#include <unistd.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

int main(int argc, char **argv)
{

  SDL_Surface *img;
  
  if(SDL_Init(SDL_INIT_VIDEO) < 0)

  {
    return EXIT_FAILURE;
  }
  
  return 0;
}
