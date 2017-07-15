/*! An abstraction class for all movable entities within the Breakout game.
 *
 *  This class encapsulates the logic and functionality required for entities 
 *  to act as moving entities in the game. It provides a logic to define the
 *  moving direction and a simple velocity to be used for the movement. It is
 *  also an extension to collideable entities, which makes all moving entites
 *  to be capable to interact with all other collideable entities.
 */
#ifndef BREAKOUT_MOVABLE_H
#define BREAKOUT_MOVABLE_H

#include "collideable.h"

namespace breakout
{
  class Movable : public Collideable
  {
  public:
    Movable(Game& game);

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
}

#endif