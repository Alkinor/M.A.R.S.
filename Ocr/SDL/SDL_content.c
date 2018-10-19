#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <unistd.h>

//Initialize the SDL2 library to allow us to do some image treatment

int init_SDL()
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      printf("Error : cannot initialize SDL");
      return 1;
    }
  return 0;
}

//Load the image

SDL_Surface * load_image(char *path)
{
  SDL_Surface *img;
  img = SDL_LoadBMP(path);
  if (!img)
    {
      printf("Error, can't load %s", path);
    }
  return img;
}

//Display the image

int display_image(SDL_Surface *img)
{
  //const int WIDTH  = 640;
  //const int HEIGHT = 480;
  
  SDL_Window *win = 0;
  SDL_Renderer *renderer = 0;
  SDL_Texture *texture = NULL;
  //int w, h;
  
  //Create the window with the image inside
  
  win = SDL_CreateWindow("Image Loading", 100, 100,  img->w, img->h, 0);
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  texture = SDL_CreateTextureFromSurface(renderer, img);
  //SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  
  
  if (!img)
    {
      printf("No image to load");
    }
  //SDL_Rect texr; texr.x = WIDTH/2; texr.y = HEIGHT/2; texr.w = w*2; texr.h = h*2; 
   if (!texture)
     {
       SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
       return 1;
     }

   //This while loop will keep the image diplayed until we decide to close the window
   
   while (1)
     {
       SDL_Event e;
       if ( SDL_PollEvent(&e) )
	 {
	   if (e.type == SDL_QUIT)
	     break;
	   else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
	     break;
	 } 
       SDL_RenderClear(renderer);
       //SDL_RenderCopy(renderer, texture, NULL, &texr);
       SDL_RenderCopy(renderer, texture, NULL, NULL);
       SDL_RenderPresent(renderer);
     }

   //Destroy the window and its component
   
   SDL_DestroyTexture(texture);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(win);
   return 0;
}

//To quit the SDL

void quit_SDL()
{
  SDL_Quit();
}

