#ifndef BREAKOUT_DRAWABLE_H
#define BREAKOUT_DRAWABLE_H

#include "entity.h"

namespace breakout
{
  class Drawable : public Entity
  {
  public:
    Drawable();
    Drawable(const SDL_Rect& rect);

    virtual ~Drawable() = default;

    void render(SDL_Renderer& renderer);

    bool isVisible() const { return mVisible; }

    void setVisible(bool visible) { mVisible = visible; }
  protected:
    SDL_Color mColor;
    bool      mVisible;
  };
}

#endif