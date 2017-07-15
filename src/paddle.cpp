#include "paddle.h"
#include "game.h"

using namespace breakout;


Paddle::Paddle(Game& game) : Movable(game), mOriginalWidth(0)
{
  // ...
}

void Paddle::shrink()
{
  // store the original width if not yet stored.
  if (mOriginalWidth == 0) {
    mOriginalWidth = mRect.w;
  }

  // shrink the paddle if it is not yet being done.
  if (mOriginalWidth == mRect.w) {
    mRect.w =  (mRect.w / 2);
    mExtentX = (mRect.w / 2);
    mRect.x = (mCenterX - mExtentX);
  }
}

void Paddle::reset()
{
  // restore the original width if necessary.
  if (mOriginalWidth != mRect.w) {
    mRect.w = mOriginalWidth;
    mExtentX = (mRect.w / 2);
  }

  // get the window client size width.
  int windowWidth;
  SDL_GetWindowSize(mGame.getWindow(), &windowWidth, nullptr);

  // restore the paddle back to the center of the screen.
  // mRect.x = ()
}
