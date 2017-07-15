#include "collideable.h"

#include <cmath>

using namespace breakout;

Collideable::Collideable(Game& game) 
  : Drawable(game),
    mEnabled(true),
    mExtentX(0),
    mExtentY(0),
    mCenterX(0),
    mCenterY(0)
{
  // ..
}

bool Collideable::collides(const Collideable& o) const
{
  // no collision if either candidate is currently disabled.
  if (mEnabled == false || o.mEnabled == false) return false;

  // perform a simple 2D AABB intersection test.
  auto x = std::abs(mCenterX - o.mCenterX) < (mExtentX + o.mExtentX);
  auto y = std::abs(mCenterY - o.mCenterY) < (mExtentY + o.mExtentY);
  return x && y;
}