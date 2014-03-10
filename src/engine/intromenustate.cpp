#include <SDL2\SDL.h>

#include <engine/intromenustate.h>

IntroMenuState IntroMenuState::IntroMenu_;

void IntroMenuState::Init()
{
  float
  //generate a vertex buffer
  glGenBuffers(1, &vertex_buffer_obj_);
}

void IntroMenuState::Cleanup()
{

}

void IntroMenuState::Pause()
{

}

void IntroMenuState::Resume()
{

}

void IntroMenuState::HandleEvents(GameEngine *game)
{
  SDL_Event event;
  if (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_Quit:
        game->Quit();
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
          case SDLK_SPACE:
          case: SDL_ESCAPE:
            game->Quit();
            break;
        }
    }
  }
}

void IntroMenuState::Update(GameEngine *game)
{

}

void IntroMenuState::Render(GameEngine *game)
{

}
