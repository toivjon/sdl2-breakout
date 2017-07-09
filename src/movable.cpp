#include "movable.h"

using namespace breakout;

Movable::Movable() : Movable({ 0,0,0,0 })
{
  // ...
}

Movable::Movable(const SDL_Rect& rect) : Collideable(rect),
  mDirectionX(0.f),
  mDirectionY(0.f),
  mVelocity(0.f)
{
  // ...
}

void Movable::move(float dt)
{
  // update the position of the entity in the x-axis.
  auto diffX = dt * mDirectionX * mVelocity;
  mRect.x += diffX;
  mCenterX += diffX;

  // update the position of the entity in the y-axis.
  auto diffY = dt * mDirectionY * mVelocity;
  mRect.y += diffY;
  mCenterY += diffY;
}