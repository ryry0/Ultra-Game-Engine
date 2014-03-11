#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <engine/gameengine.h>

/*
 * Description:
 *  This class defines the interface of the game state.
 *  All main game states (main menu, pause screen, in game, victory, etc)
 *  shall derive from this class.
 *
 * Functions:
 *  Init:     Initializes needed resources when entering this state.
 *  Cleanup:  Destroys allocated resources when exiting this state.
 *  Pause:    Deals with state interruption, i.e. if the state is interrupted
 *    but will be resumed later.
 *  Resume:   The state continues if it was Pause()d.
 *  HandleEvents: This state's own interpretation of keyboard/mouse events.
 *  Update:       How this state updates it's own internal logic (menu vs game).
 *  Render:       What this state will draw to the screen.
 */


class GameState
{
  public:
    virtual void Init   () = 0;
    virtual void Cleanup() = 0;

    virtual void Pause  () = 0;
    virtual void Resume () = 0;

    virtual void HandleEvents (GameEngine *game) = 0;
    virtual void Update       (GameEngine *game) = 0;
    virtual void Render       (GameEngine *game) = 0;

    void ChangeState(GameEngine *game, GameState *state)
    {game->ChangeState(state);}
  protected:
    GameState() {}
};

#endif
