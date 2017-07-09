#ifndef BREAKOUT_COLLIDEABLE_H
#define BREAKOUT_COLLIDEABLE_H

#include "drawable.h"

namespace breakout
{
  class Collideable : public Drawable
  {
  public:
    Collideable();
    Collideable(const SDL_Rect& rect);

    virtual ~Collideable() = default;

    bool collides(const Collideable& o) const;

    bool isEnabled() const { return mEnabled; }

    void setEnabled(bool enabled) { mEnabled = enabled; }
  protected:
    bool  mEnabled;
    int   mExtentX;
    int   mExtentY;
    int   mCenterX;
    int   mCenterY;
  };
}

#endif