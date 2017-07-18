/*! A paddle implementation for the Breakout game.
 *
 *  This class encapsulates all the additional data required to manage a game
 *  paddle that acts as a player avatar in the Breakout game. Paddle is itself
 *  a simple rectangle component that is simply handled by the user by pressing
 *  the movement buttons. In two player games, both players may share the same
 *  avatar instance as the players are not playing the game at the same time.
 */
#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H

#include "movable.h"

namespace breakout
{
  class Paddle final : public Movable
  {
  public:
    Paddle(Game& game);

    void shrink();
    void reset();
    void update(float dt);
  private:
    int mOriginalWidth;
  };
}

#endif