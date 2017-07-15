#include "movable.h"

using namespace breakout;

Movable::Movable(Game& game)
  : Collideable(game),
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
  mRect.x += static_cast<int>(diffX);
  mCenterX += static_cast<int>(diffX);

  // update the position of the entity in the y-axis.
  auto diffY = dt * mDirectionY * mVelocity;
  mRect.y += static_cast<int>(diffY);
  mCenterY += static_cast<int>(diffY);
}