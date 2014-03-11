#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <engine/gameengine.h>

namespace engine
{
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
  private:
    GameState() {}
};
}
#endif
