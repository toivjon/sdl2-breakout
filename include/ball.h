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