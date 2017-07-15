/*! An abstraction class for all collideable entities within the Breakout game.
 *
 *  This class encapsulates the necessary collision detection definitions for a
 *  game entity to became a physically collideable instance within the game. It
 *  uses a simple AABB structure as a bounding volume which can be also toggled
 *  on/off with a simple enabled flag. Class extents the drawable class, which
 *  provides a support for also making all collideable entities to be rendered.
 */
#ifndef BREAKOUT_COLLIDEABLE_H
#define BREAKOUT_COLLIDEABLE_H

#include "drawable.h"

namespace breakout
{
  class Collideable : public Drawable
  {
  public:
    Collideable(Game& game);

    virtual ~Collideable() = default;

    bool collides(const Collideable& o) const;

    void setX(int x) override;
    void setY(int y) override;

    void setWidth(int width)   override;
    void setHeight(int height) override;

    bool isEnabled() const { return mEnabled; }
    int getExtentX() const { return mExtentX; }
    int getExtentY() const { return mExtentY; }
    int getCenterX() const { return mCenterX; }
    int getCenterY() const { return mCenterY; }

    void setEnabled(bool enabled) { mEnabled = enabled; }
    void setExtentX(int extentX)  { mExtentX = extentX; }
    void setExtentY(int extentY)  { mExtentY = extentY; }
    void setCenterX(int centerX)  { mCenterX = centerX; }
    void setCenterY(int centerY)  { mCenterY = centerY; }
  protected:
    bool  mEnabled;
    int   mExtentX;
    int   mExtentY;
    int   mCenterX;
    int   mCenterY;
  };
}

#endif