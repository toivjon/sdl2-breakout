#include "drawable.h"

#include <memory>

using namespace breakout;

Drawable::Drawable() : Drawable({ 0,0,0,0 })
{
  // ...
}

Drawable::Drawable(const SDL_Rect& rect) : Entity(rect),
  mColor({ 0xff, 0xff, 0xff, 0xff }),
  mVisible(true)
{
  // ...
}

void Drawable::render(SDL_Renderer& renderer)
{
  if (mVisible) {
    SDL_SetRenderDrawColor(&renderer, mColor.r, mColor.g, mColor.b, mColor.a);
    SDL_RenderFillRect(&renderer, &mRect);
  }
}