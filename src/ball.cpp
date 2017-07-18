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

// A helper utility to check whether the two SDL colors are same.
inline bool equals(const SDL_Color& c1, const SDL_Color& c2) {
  return (c1.a == c2.a && c1.b == c2.b && c1.g == c2.g && c1.r == c2.r);
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
    mState(State::NORMAL),
    mHitCount(0),
    mOrangeBricksHit(false),
    mRedBricksHit(false)
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
  mHitCount = 0;
  mOrangeBricksHit = false;
  mRedBricksHit = false;
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
    incrementHitCount();
    // TODO shrink the paddle.
  }

  // check whether the ball collides with the left wall.
  const auto& leftWall = courtScene->getLeftWall();
  if (mDirectionX < 0.f && collides(leftWall)) {
    setDirectionX(-getDirectionX());
    mState = State::NORMAL;
    incrementHitCount();
  }

  // check whether the ball collides with the right wall.
  const auto& rightWall = courtScene->getRightWall();
  if (mDirectionX > 0.f && collides(rightWall)) {
    setDirectionX(-getDirectionX());
    mState = State::NORMAL;
    incrementHitCount();
  }

  // check whether the ball collides with the paddle.
  const auto& paddle = courtScene->getPaddle();
  if (mDirectionY > 0.f && collides(paddle)) {
    auto xDiff = static_cast<float>(mCenterX - paddle.getCenterX());
    mState = State::NORMAL;
    incrementHitCount();

    auto newDirection = std::array<float, 2>();
    newDirection[0] = (xDiff / (((float)paddle.getWidth()) / 2.f));
    newDirection[1] = -getDirectionY();
    newDirection = normalize(newDirection);
    setDirectionX(newDirection[0]);
    setDirectionY(newDirection[1]);
  }

  // TODO check whether the ball hits the out-of-bounds detector.
  if (mState != State::BRICK_HIT) {
    // resolve the current player and level and get a reference to level bricks.
    auto courtScene = std::dynamic_pointer_cast<CourtScene>(mGame.getScene());
    auto player = courtScene->getActivePlayer();
    auto level = courtScene->getPlayerLevel(player);
    auto& bricks = courtScene->getBricks(player, level);

    // check whether the ball hits with the court bricks.
    for (auto& brick : bricks) {
      if (collides(brick)) {
        // TODO check for the end-game-mode.

        // disable the brick from the level.
        brick.setVisible(false);
        brick.setEnabled(false);

        // perform actions base on the color of the brick we just hit.
        if (equals(brick.getColor(), CourtScene::BRICKS_1_FILL_STYLE)) {
          courtScene->addPlayerScore(player, 1);
        } else if (equals(brick.getColor(), CourtScene::BRICKS_2_FILL_STYLE)) {
          courtScene->addPlayerScore(player, 3);
        } else if (equals(brick.getColor(), CourtScene::BRICKS_3_FILL_STYLE)) {
          courtScene->addPlayerScore(player, 5);
          if (mOrangeBricksHit == false) {
            incrementVelocity();
            mOrangeBricksHit = true;
          }
        } else if (equals(brick.getColor(), CourtScene::BRICKS_4_FILL_STYLE)) {
          courtScene->addPlayerScore(player, 7);
          if (mRedBricksHit == false) {
            incrementVelocity();
            mRedBricksHit = true;
          }
        }

        // add a hit into the hit counter.
        incrementHitCount();

        // TODO calculate the amount of destroyed bricks.
        // TODO check whether to end the scene / game.

        // change the ball state to require a paddle of wall hit next.
        mState = State::BRICK_HIT;

        // invert the ball y-axis direction.
        mDirectionY = -mDirectionY;
        break;
      }
    }

  }

  // TODO

  // move the ball.
  move(dt);
}

void Ball::incrementHitCount()
{
  mHitCount++;
  if (mHitCount == 4 || mHitCount == 12) {
    incrementVelocity();
  }
}

void Ball::incrementVelocity()
{
  mVelocity += mVelocityIncrementStep;
}