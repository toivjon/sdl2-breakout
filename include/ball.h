#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include "movable.h"

namespace breakout
{
  class Ball final : public Movable
  {
  public:
    Ball();
    Ball(const SDL_Rect& rect);
  private:
    int mInitialVelocity;
    int mVelocityIncrementStep;
  };
}

#endif