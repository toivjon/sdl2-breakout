#include "movable.h"

#include <cmath>

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
  // define a suitable epsilon for float comparisons.
  static const auto epsilon = 0.00001f;

  // update the position of the entity in the x-axis.
  if (std::fabs(mDirectionX) > epsilon) {
    auto diffX = dt * mDirectionX * mVelocity;
    mRect.x += static_cast<int>(diffX);
    mCenterX += static_cast<int>(diffX);
  }

  // update the position of the entity in the y-axis.
  if (std::fabs(mDirectionY) > epsilon) {
    auto diffY = dt * mDirectionY * mVelocity;
    mRect.y += static_cast<int>(diffY);
    mCenterY += static_cast<int>(diffY);
  }
}