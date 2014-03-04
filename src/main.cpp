/*
 * Author: Ryan - David Reyes
 * Description:
 */
#include <iostream>
#include <iomanip>
#include <SDL2/SDL.h>

int main(int argc, char ** argv)
{

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
    return 1;
  }
  SDL_Quit();

  return 0;
}
