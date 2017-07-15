#include "drawable.h"

using namespace breakout;

Drawable::Drawable(Game& game)
  : Entity(game),
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