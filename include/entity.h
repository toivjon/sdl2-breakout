#ifndef BREAKOUT_ENTITY_H
#define BREAKOUT_ENTITY_H

#include <SDL.h>

namespace breakout
{
  class Entity
  {
  public:
    Entity() : Entity({ 0,0,0,0 }) {}
    Entity(const SDL_Rect& rect) : mRect(rect) {}

    virtual ~Entity() = default;

    int getX() const      { return mRect.x; }
    int getY() const      { return mRect.y; }
    int getWidth() const  { return mRect.w; }
    int getHeight() const { return mRect.h; }

    void setX(int x)      { mRect.x = x; }
    void setY(int y)      { mRect.y = y; }
    void setWidth(int w)  { mRect.w = w; }
    void setHeight(int h) { mRect.h = h; }
  protected:
    SDL_Rect mRect;
  };
}

#endif