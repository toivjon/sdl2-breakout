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
  default:
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
    mRedBricksHit(false),
    mEndGameMode(false)
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
  auto player = courtScene->getActivePlayer();

  // check whether the ball collides with the top wall.
  const auto& topWall = courtScene->getTopWall();
  if (mDirectionY < 0.f && collides(topWall)) {
    setDirectionY(-getDirectionY());
    mState = State::NORMAL;
    incrementHitCount();
    courtScene->getPaddle().shrink();
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

  // check whether the ball has entered so called out-of-bounds area.
  // after the ball enters this section, it is considered as being lost.
  // game ends i.e. goes into end animation after the last ball is used.
  // two player games will also need to change the player index here.
  if (mDirectionY > 0.f && collides(courtScene->getOutOfBoundsDetector())) {
    courtScene->incrementBallIndex(player);
    courtScene->resetBallAndPaddle();
    if (mGame.getPlayMode() == Game::PlayMode::SINGLE_PLAYER) {
      if (courtScene->getPlayerBallIndex(player) > 3) {
        courtScene->endGame();
      }
    } else {
      // hidden special case, which may occur only in two player games.
      // here an additional level is added to second player levels if
      // the first player has completed the first level with the third
      // ball and whether the ball gets off-the-screen immediately by
      // not hiting any bricks before. This hidden speciality allows
      // the second player to achieve the maximum of 1344 points instead
      // of the normal 896 points, which is available with two levels.
      if (player == CourtScene::Player::PLAYER_1) {
        if (courtScene->getPlayerBallIndex(player) > 3) {
          if (courtScene->getPlayerLevel(player) == 1) {
            auto& bricks = courtScene->getBricks(player, 1);
            courtScene->addPlayerLevel(bricks, CourtScene::Player::PLAYER_2);
          }
        }
      }

      // check whether it's time to end the game or a time to change player.
      if (courtScene->getPlayerBallIndex(CourtScene::Player::PLAYER_1) > 3
       && courtScene->getPlayerBallIndex(CourtScene::Player::PLAYER_2)) {
        courtScene->endGame();
      } else {
        courtScene->switchPlayer();
      }
    }
  } else if (mState != State::BRICK_HIT) {
    // get the current level and get a reference to level bricks.
    auto level = courtScene->getPlayerLevel(player);
    auto& bricks = courtScene->getBricks(player, level);

    // check whether the ball hits with the court bricks.
    for (auto& brick : bricks) {
      if (collides(brick)) {
        if (mEndGameMode == false) {
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

          // calculate the amount of destroyed bricks.
          auto destroyedBricks = 0u;
          for (auto& brick : bricks) {
            if (brick.isVisible() == false) {
              destroyedBricks++;
            }
          }

          // check whether the end of this level has been reached.
          // this requires that the player just destroyed the last brick.
          // we need to goto next level or check whether to end the game.
          if (destroyedBricks == bricks.size()) {
            courtScene->resetBallAndPaddle();
            if ((courtScene->getPlayerLevel(player) + 1) >= courtScene->getPlayerLevelCount(player)) {
              courtScene->setPlayerBallIndex(player, 4);
            } else {
              courtScene->setPlayerLevel(player, courtScene->getPlayerLevel(player) + 1);
            }
            if (mGame.getPlayMode() == Game::PlayMode::SINGLE_PLAYER) {
              if (courtScene->getPlayerBallIndex(player) > 3) {
                courtScene->endGame();
              }
            } else {
              if (courtScene->getPlayerBallIndex(CourtScene::Player::PLAYER_1) > 3
                && courtScene->getPlayerBallIndex(CourtScene::Player::PLAYER_2)) {
                courtScene->endGame();
              } else {
                courtScene->switchPlayer();
              }
            }
          }
        }

        // change the ball state to require a paddle of wall hit next.
        mState = State::BRICK_HIT;

        // invert the ball y-axis direction.
        mDirectionY = -mDirectionY;
        break;
      }
    }

  }
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