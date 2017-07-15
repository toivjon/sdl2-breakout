#include "paddle.h"
#include "court_scene.h"
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
  mRect.x = (windowWidth / 2) - mExtentX;
  mCenterX = mRect.x + mExtentX;
}

void Paddle::update(float dt)
{
  // ensure movement (if any).
  move(dt);

  // check whether the paddle collides with the left or right wall.
  auto scene = mGame.getScene();
  auto courtScene = static_cast<CourtScene*>(scene.get());
  if (courtScene != nullptr) {
    auto& leftWall = courtScene->getLeftWall();
    auto& rightWall = courtScene->getRightWall();
    if (mDirectionX < 0.f && leftWall.collides(*this)) {
      mRect.x = leftWall.getX() + leftWall.getExtentX() * 2;
      mCenterX = mRect.x + mExtentX;
    } else if (rightWall.collides(*this)) {
      mRect.x = rightWall.getX() - mExtentX * 2;
      mCenterX = mRect.x + mExtentX;
    }
  }
}