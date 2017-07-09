#ifndef BREAKOUT_MOVABLE_H
#define BREAKOUT_MOVABLE_H

#include "collideable.h"

namespace breakout
{
  class Movable : public Collideable
  {
  public:
    Movable();
    Movable(const SDL_Rect& rect);

    virtual ~Movable() = default;

    void move(float dt);

    float getDirectionX() const { return mDirectionX; }
    float getDirectionY() const { return mDirectionY; }
    float getVelocity() const   { return mVelocity;   }

    void setDirectionX(float x) { mDirectionX = x;  }
    void setDirectionY(float y) { mDirectionY = y;  }
    void setVelocity(float v)   { mVelocity = v;    }
  protected:
    float mDirectionX;
    float mDirectionY;
    float mVelocity;
  };
// ...
}

#endif