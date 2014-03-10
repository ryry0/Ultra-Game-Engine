#ifndef INTRO_MENU_STATE_H_
#define INTRO_MENU_STATE_H_

#include <engine/gamestate.h>

/*
 * Intro Menu State represents the main menu of the game.
 * It will be the first state that the game enters upon running.
 * From there you will be able to configure the settings and
 * start the game. Because of the polymorphic state system,
 * all code pertaining to the main menu is defined in this class.
 * All you need to do is implement each of the functions.
 *
 * States control whether or not there is a state change, not the main loop.
 * It is up to your own implementation to make sure that it changes states
 * at the right time.
 */
class IntroMenuState : public GameState
{
  public:
    void Init   ();
    void Cleanup();

    void Pause  ();
    void Resume ();

    void HandleEvents (GameEngine *game);
    void Update       (GameEngine *game);
    void Render       (GameEngine *game);

    static IntroMenuState * Instance()
    {return &IntroMenu_;}

  protected:
    IntroMenuState() {}

  private:
    static IntroMenuState IntroMenu_;
    Gluint vertex_buffer_obj_;
};
#endif
