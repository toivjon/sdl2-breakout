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
    mBall(game)
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
}

CourtScene::~CourtScene()
{
  // ...
}

void CourtScene::update()
{
  // ...
}

void CourtScene::render()
{
  auto& renderer = mGame.getRenderer();
  mLeftWall.render(renderer);
  mRightWall.render(renderer);
  mTopWall.render(renderer);
  mBall.render(renderer);
}

void CourtScene::enter()
{
  // ...
}

void CourtScene::keyDown(SDL_KeyboardEvent& event)
{
  // ...
}

void CourtScene::keyUp(SDL_KeyboardEvent& event)
{
  // ...
}