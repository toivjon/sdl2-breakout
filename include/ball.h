/*! The ball encapsulation for the Breakout game.
 *
 *  This class encapsulates the presentation and the logic for the ball in the
 *  Breakout game. The main collision logic is implemented within the functions
 *  in this class, where the ball behaviour is changed based on the collided
 *  objects. Also the main logic to check the game end and switching between
 *  the players are launched from the ball implementation.
 */
#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include "movable.h"

namespace breakout
{
  class Ball final : public Movable
  {
  public:
    enum class State { NORMAL, BRICK_HIT };

    Ball(Game& game);

    void reset();
    void update(float dt);

    void incrementHitCount();
    void incrementVelocity();

    void setEndGameMode(bool mode) { mEndGameMode = mode; }

    float getInitialVelocity() const { return mInitialVelocity; }
  private:
    float mInitialVelocity;
    float mVelocityIncrementStep;
    State mState;
    int   mHitCount;
    bool  mOrangeBricksHit;
    bool  mRedBricksHit;
    bool  mEndGameMode;
  };
}

#endif