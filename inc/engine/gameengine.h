#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_
#include <stack>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

/*
 * Description:
 *  The GameEngine class is used to manage the game states.
 *  The main game loop is located in main(), and GameEngine uses dynamic
 *  dispatch to substitute the HandleEvents, Update, and Render Functions,
 *  with Derived ones defined in the GameState.
 *
 * Functions:
 *  Init:         Creates Window context.
 *  Cleanup:      Destroys window context.
 *  ChangeState:  Changes the current state of the program to 'state'.
 *  PushState:    Pushes a state to the stack, so you can return to it later.
 *  PopState:     Pops the topmost state off the stack.
 *  Update:       Calls the GameState Implementation of Update()
 *  Render:       Calls the GameState Implementation of Render()
 *  HandleEvents: Calls the GameState Implementation of HandleEvents()
 */
class GameState;

class GameEngine
{
  public:
    int  Init   ();
    void Cleanup();

    void ChangeState(GameState *state);
    void PushState  (GameState *state);
    void PopState();

    void HandleEvents ();
    void Update       ();
    void Render       ();

    bool IsRunning()  {return running_;}

    void Quit     () {running_ = false;}

  private:
    void CheckGLSupport(GLenum error);
  private:
    bool running_;
    SDL_Window *window_;
    SDL_GLContext context_;
    std::stack<GameState*> state_stack_;
};
#endif
