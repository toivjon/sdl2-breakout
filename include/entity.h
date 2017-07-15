/*! The root abstraction for all entities within the Breakout game.
 * 
 *  This entity encapsulates the functionality and attributes for all entities
 *  that are used within the game application. In this Breakout game version we
 *  require each entity to have at least 2d-position and size. In addition, we
 *  also want that each entity has an injected reference to root game instance.
 */
#ifndef BREAKOUT_ENTITY_H
#define BREAKOUT_ENTITY_H

#include <SDL.h>

namespace breakout
{
  class Game;
  class Entity
  {
  public:
    Entity(Game& game) : mGame(game), mRect({ 0, 0, 0, 0}) {}

    virtual ~Entity() = default;

    int getX() const      { return mRect.x; }
    int getY() const      { return mRect.y; }
    int getWidth() const  { return mRect.w; }
    int getHeight() const { return mRect.h; }

    virtual void setX(int x)      { mRect.x = x; }
    virtual void setY(int y)      { mRect.y = y; }
    virtual void setWidth(int w)  { mRect.w = w; }
    virtual void setHeight(int h) { mRect.h = h; }
  protected:
    Game&    mGame;
    SDL_Rect mRect;
  };
}

#endif