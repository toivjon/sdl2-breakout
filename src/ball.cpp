#include "ball.h"
#include "court_scene.h"
#include "game.h"

#include <array>
#include <cmath>
#include <random>

using namespace breakout;

// A helper utility to normalize the given vector.
inline std::array<float, 2> normalize(const std::array<float, 2>& value)
{
  auto length = std::sqrt(std::pow(value[0], 2) + std::pow(value[1], 2));
  return { value[0] / length, value[1] / length };
}

// A helper utility to construct a new initial direction for the ball.
inline std::array<float, 2> createRandomInitDirection()
{
  switch ((std::rand() * 10) % 3) {
  case 0:
    return normalize({ 0.f, 1.f });
  case 1:
    return normalize({ 0.5f, 0.5f });
  case 2:
    return normalize({ -0.5f, 0.5f });
  }
}

Ball::Ball(Game& game)
  : Movable(game),
    mInitialVelocity(0),
    mVelocityIncrementStep(0),
    mState(State::NORMAL)
{
  // query the window size from the window instance
  int windowWidth, windowHeight;
  SDL_GetWindowSize(mGame.getWindow(), &windowWidth, &windowHeight);

  // calculate velocity definitions for the ball.
  mInitialVelocity = (windowHeight / 2370.f);
  mVelocityIncrementStep = (windowHeight / 6330.f);

  // reset the ball state.
  reset();
}

void Ball::reset()
{
  // query the window size from the window instance
  int windowWidth, windowHeight;
  SDL_GetWindowSize(mGame.getWindow(), &windowWidth, &windowHeight);

  // set the ball back into the middle of the screen.
  setX((windowWidth / 2) - mExtentX);
  setY((windowHeight / 2) - mExtentY);

  // clear and stop movement definitions.
  auto direction = createRandomInitDirection();
  setVelocity(0.f);
  setDirectionX(direction[0]);
  setDirectionY(direction[1]);

  mState = State::NORMAL;
  setVisible(false);
}

void Ball::update(float dt)
{
  // skipt update functionality if the ball is not visible.
  if (isVisible() == false) return;

  auto scene = mGame.getScene();
  auto courtScene = std::dynamic_pointer_cast<CourtScene>(scene);

  // check whether the ball collides with the top wall.
  const auto& topWall = courtScene->getTopWall();
  if (mDirectionY < 0.f && collides(topWall)) {
    setDirectionY(-getDirectionY());
    mState = State::NORMAL;
    // TODO increment hit count.
    // TODO shrink the paddle.
  }

  // check whether the ball collides with the left wall.
  const auto& leftWall = courtScene->getLeftWall();
  if (mDirectionX < 0.f && collides(leftWall)) {
    setDirectionX(-getDirectionX());
    mState = State::NORMAL;
    // TODO increment hit count.
  }

  // check whether the ball collides with the right wall.
  const auto& rightWall = courtScene->getRightWall();
  if (mDirectionX > 0.f && collides(rightWall)) {
    setDirectionX(-getDirectionX());
    mState = State::NORMAL;
    // TODO increment hit count.
  }

  // check whether the ball collides with the paddle.
  const auto& paddle = courtScene->getPaddle();
  if (mDirectionY > 0.f && collides(paddle)) {
    auto xDiff = static_cast<float>(mCenterX - paddle.getCenterX());
    mState = State::NORMAL;
    // TODO increment the hit count.

    auto newDirection = std::array<float, 2>();
    newDirection[0] = (xDiff / (((float)paddle.getWidth()) / 2.f));
    newDirection[1] = -getDirectionY();
    newDirection = normalize(newDirection);
    setDirectionX(newDirection[0]);
    setDirectionY(newDirection[1]);
  }

  // TODO

  // move the ball.
  move(dt);
}