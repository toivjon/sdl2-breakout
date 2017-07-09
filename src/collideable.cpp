#include "collideable.h"

#include <cmath>

using namespace breakout;

Collideable::Collideable() : Collideable({ 0,0,0,0 })
{
  // ...
}

Collideable::Collideable(const SDL_Rect& rect) : Drawable(rect),
  mEnabled(true),
  mExtentX(rect.w / 2),
  mExtentY(rect.h / 2),
  mCenterX(rect.x - rect.w),
  mCenterY(rect.y - rect.h)
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