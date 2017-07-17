#include "court_scene.h"
#include "game.h"

#include <SDL.h>

using namespace breakout;

// The divisor of the slot width related to window client area width.
#define SLOT_WIDTH_DIVISOR  16
// the divisor of the slot height related to window client area width.
#define SLOT_HEIGHT_DIVISOR 45

CourtScene::CourtScene(Game& game)
  : Scene(game),
    mLeftWall(game),
    mRightWall(game),
    mTopWall(game),
    mBall(game),
    mPaddle(game)
{
  // query the window size from the window instance
  int windowWidth, windowHeight;
  SDL_GetWindowSize(mGame.getWindow(), &windowWidth, &windowHeight);
  auto windowHalfWidth = (windowWidth / 2);
  auto windowHalfHeight = (windowHeight / 2);

  // precalculate some relative size definitions.
  auto slotWidth = (windowWidth / SLOT_WIDTH_DIVISOR);
  auto slotHeight = (windowWidth / SLOT_HEIGHT_DIVISOR);
  auto slotHalfWidth = (slotWidth / 2);
  auto slotHalfHeight = (slotHeight / 2);
  
  // define left wall props.
  mLeftWall.setX(0);
  mLeftWall.setY(0);
  mLeftWall.setWidth(slotHeight);
  mLeftWall.setHeight(windowHeight);

  // define right wall props.
  mRightWall.setX(windowWidth - slotHeight);
  mRightWall.setY(0);
  mRightWall.setWidth(slotHeight);
  mRightWall.setHeight(windowHeight);

  // define top wall props.
  mTopWall.setX(0);
  mTopWall.setY(0);
  mTopWall.setWidth(windowWidth);
  mTopWall.setHeight(slotHeight);

  // define props for the ball.
  mBall.setX(windowHalfWidth - slotHalfHeight);
  mBall.setY(windowHalfHeight - slotHalfHeight);
  mBall.setWidth(slotHeight);
  mBall.setHeight(slotHeight);

  // define props for the paddle.
  mPaddle.setColor({ 0x00, 0xff, 0xff, 0xff });
  mPaddle.setVelocity((static_cast<float>(windowHeight) / 1350.f));
  mPaddle.setX(windowHalfWidth - slotHalfWidth);
  mPaddle.setY(windowHeight - 100);
  mPaddle.setWidth(slotWidth);
  mPaddle.setHeight(slotHeight);
}

CourtScene::~CourtScene()
{
  // ...
}

void CourtScene::update(float dt)
{
  // ...
  mPaddle.update(dt);
}

void CourtScene::render()
{
  auto& renderer = mGame.getRenderer();
  mLeftWall.render(renderer);
  mRightWall.render(renderer);
  mTopWall.render(renderer);
  mBall.render(renderer);
  mPaddle.render(renderer);
}

void CourtScene::enter()
{
  // ...
}

void CourtScene::keyDown(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_LEFT:
    mPaddle.setDirectionX(-1.f);
    break;
  case SDLK_RIGHT:
    mPaddle.setDirectionX(1.f);
    break;
  case SDLK_SPACE:
    if (std::fabs(mBall.getVelocity()) < 0.00001f && !mBall.isVisible()) {
      // TODO requires mBall.initial_velocity mBall.setVelocity()
      mBall.setVisible(true);
    }
    break;
  }
}

void CourtScene::keyUp(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_LEFT:
    if (std::fabs(mPaddle.getDirectionX() + 1.f) < 0.00001f) {
      mPaddle.setDirectionX(0.f);
    }
    break;
  case SDLK_RIGHT:
    if (std::fabs(mPaddle.getDirectionX() - 1.f) < 0.00001f) {
      mPaddle.setDirectionX(0.f);
    }
    break;
  case SDLK_SPACE:
    break;
  }
}