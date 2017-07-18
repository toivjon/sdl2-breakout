/*! An abstraction class for all drawable entities within the Breakout game.
 *
 *  This class encapsulates the necessary draw instructions required to make
 *  entities drawable. It is an immediate extension to the root entity class,
 *  which stores all necessary size and position instructions. The drawing
 *  logic as well as the detailed instructions (i.e. color and visibility) are
 *  considered and a mandatory part of this extension.
 */
#ifndef BREAKOUT_DRAWABLE_H
#define BREAKOUT_DRAWABLE_H

#include "entity.h"

namespace breakout
{
  class Drawable : public Entity
  {
  public:
    Drawable(Game& game);

    virtual ~Drawable() = default;

    virtual void render(SDL_Renderer& renderer);

    bool isVisible() const              { return mVisible;  }
    const SDL_Color& getColor() const   { return mColor;    }

    void setVisible(bool visible)         { mVisible = visible; }
    void setColor(const SDL_Color& color) { mColor = color;     }
  protected:
    SDL_Color mColor;
    bool      mVisible;
  };
}

#endif