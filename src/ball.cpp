#include "ball.h"

using namespace breakout;

Ball::Ball() : Ball({ 0,0,0,0 })
{
  // ...
}

Ball::Ball(const SDL_Rect& rect) : Movable(rect)
{
  // ...
}