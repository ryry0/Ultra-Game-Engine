/*
 * Author: Ryan - David Reyes
 * Description:
 */
//standard includes
#include <iostream>
#include <iomanip>

//external library includes
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>

//program includes
#include <engine/gameengine.h>

int main(int argc, char ** argv)
{
  int return_value = 0;

  //Create the game context
  GameEngine game;

  //start the game
  return_value = game.Init();

  //main loop
  while (game.IsRunning())
  {
    game.HandleEvents();
    game.Update();
    game.Render();
  }

  //delete the game
  game.Cleanup();
  return return_value;
}
