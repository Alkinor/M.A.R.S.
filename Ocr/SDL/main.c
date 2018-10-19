#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL_content.h"
#include "pixel_access.h"
#include "binarize.h"
#include "segmentation.h"
#include "matrix_content.h"

int main()
{
  if(init_SDL() != 0)
  {
    return 1;
  }
  SDL_Surface *image = load_image("header_comic.bmp");
  //SDL_Surface *img;
  //SDL_Surface *p;
  binarize(image);
  lineDetect(image);
  charDetect(image);
  //int l = firstCharacter(image, 49);
  //int m = lastCharacter(image, 49);
  // int p = averageSpace(image, l, m, 49);
  //printf("%i\n", l);
  //printf("%i\n", m);
  //printf("%i\n", p);
  //img = displayWords(image, 49, 100);
  //p = redimension(img, 500, 500);
  //binarize(img);
  //Matrix matrix = convert_to_matrix(img);
  //Matrix matrix = ConstructMatrix(5, 5);
  //matrix.mat[1 + 1 + matrix.mat] = 1;
  //printMatrix(matrix);
  display_image(image);
  //detect_char(image);
  //56, 49, 95, 100
  //binarize(image);
  //display_image(image);
  //int i = delimit_char (image, 49, 57);
  //printf("%i\n", i);
  //display_texture("imagetest.png");
  quit_SDL();
  return 0;
}
