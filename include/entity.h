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
    Entity(const Entity& o) : mRect(o.mRect) {}
    Entity(Entity&& o) : mRect(o.mRect) {}

    Entity& operator=(const Entity& o) { mRect = o.mRect; return *this; }
    Entity& operator=(Entity&& o) { mRect = o.mRect; return *this; }

    virtual ~Entity() {}

    int getX() const      { return mRect.x; }
    int getY() const      { return mRect.y; }
    int getWidth() const  { return mRect.w; }
    int getHeight() const { return mRect.h; }

    void setX(int x)      { mRect.x = x; }
    void setY(int y)      { mRect.y = y; }
    void setWidth(int w)  { mRect.w = w; }
    void setHeight(int h) { mRect.h = h; }
  private:
    SDL_Rect mRect;
  };
}

#endif