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

    float getInitialVelocity() const { return mInitialVelocity; }
  private:
    float mInitialVelocity;
    float mVelocityIncrementStep;
    State mState;
  };
}

#endif