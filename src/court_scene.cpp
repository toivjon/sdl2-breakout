#include "court_scene.h"
#include "game.h"

#include <SDL.h>

using namespace breakout;

// The divisor of the slot width related to window client area width.
#define SLOT_WIDTH_DIVISOR  16
// the divisor of the slot height related to window client area width.
#define SLOT_HEIGHT_DIVISOR 45

const SDL_Color CourtScene::BRICKS_1_FILL_STYLE = { 0xff, 0xf0, 0x00, 0xff };
const SDL_Color CourtScene::BRICKS_2_FILL_STYLE = { 0x00, 0x80, 0x00, 0xff };
const SDL_Color CourtScene::BRICKS_3_FILL_STYLE = { 0xff, 0xa5, 0x00, 0xff };
const SDL_Color CourtScene::BRICKS_4_FILL_STYLE = { 0xff, 0x00, 0x00, 0xff };

CourtScene::CourtScene(Game& game)
  : Scene(game),
    mActivePlayer(Player::PLAYER_1),
    mPlayerLevel({0, 0}),
    mLeftWall(game),
    mRightWall(game),
    mTopWall(game),
    mBall(game),
    mPaddle(game),
    mPlayerIndexDigit(game),
    mPlayerBallIndexDigit(game)
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
  auto digitHeight = (slotHeight * 5);
  auto slotSpacing = (windowWidth - (2 * slotHeight) - (14 * slotWidth)) / 13;
  
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

  // build the digit indicating the current player.
  mPlayerIndexDigit.setX(slotHeight);
  mPlayerIndexDigit.setY(slotHeight);
  mPlayerIndexDigit.setWidth(slotWidth);
  mPlayerIndexDigit.setHeight(digitHeight);
  mPlayerIndexDigit.setValue(1);

  // build the digit indicating the current ball index.
  mPlayerBallIndexDigit.setX(windowHalfWidth);
  mPlayerBallIndexDigit.setY(slotHeight);
  mPlayerBallIndexDigit.setWidth(slotWidth);
  mPlayerBallIndexDigit.setHeight(digitHeight);
  mPlayerBallIndexDigit.setValue(1);

  // reserve slots for the player score digit vectors.
  mPlayerScoreDigits.resize(2);

  // build the digits used to show the score for the first player.
  mPlayerScoreDigits[0].resize(4, mGame);
  auto scoreDigitY = (slotHeight + digitHeight + slotSpacing);
  auto scoreDigitX = slotHeight;
  for (auto i = 0; i < 4; i++) {
    mPlayerScoreDigits[0][i].setY(scoreDigitY);
    mPlayerScoreDigits[0][i].setX(scoreDigitX);
    mPlayerScoreDigits[0][i].setWidth(slotWidth);
    mPlayerScoreDigits[0][i].setHeight(digitHeight);
    scoreDigitX += slotWidth + slotSpacing;
  }
  
  // build the digits used to show the score for the second player.
  mPlayerScoreDigits[1].resize(4, mGame);
  scoreDigitX = windowHalfWidth;
  for (auto i = 0; i < 4; i++) {
    mPlayerScoreDigits[1][i].setY(scoreDigitY);
    mPlayerScoreDigits[1][i].setX(scoreDigitX);
    mPlayerScoreDigits[1][i].setWidth(slotWidth);
    mPlayerScoreDigits[1][i].setHeight(digitHeight);
    scoreDigitX += slotWidth + slotSpacing;
  }

  // hide hidden score indicators (fourst numbers).
  mPlayerScoreDigits[0][0].setVisible(false);
  mPlayerScoreDigits[1][0].setVisible(false);

  // initialize bricks for both players.
  mPlayerBricks.resize(2);
  mPlayerBricks[0].resize(2);
  mPlayerBricks[1].resize(2);
  mPlayerBricks[0][0].resize(112, mGame);
  mPlayerBricks[0][1].resize(112, mGame);
  mPlayerBricks[1][0].resize(112, mGame);
  mPlayerBricks[1][1].resize(112, mGame);

  // construct brick definitions for all levels.
  auto y = scoreDigitY + digitHeight + slotSpacing;
  for (auto i = 0u; i < 8; i++) {
    // resolve the color to be used within the current row index.
    SDL_Color color;
    if (i < 2) {
      color = CourtScene::BRICKS_4_FILL_STYLE;
    } else if (i < 4) {
      color = CourtScene::BRICKS_3_FILL_STYLE;
    } else if (i < 6) {
      color = CourtScene::BRICKS_2_FILL_STYLE;
    } else {
      color = CourtScene::BRICKS_1_FILL_STYLE;
    }

    // start placing from the left wall.
    auto x = slotHeight;

    // create all bricks for both players and for all levels.
    for (auto j = 0u; j < 14; j++) {
      auto index = (i * 14) + j;
      mPlayerBricks[0][0][index].setX(x);
      mPlayerBricks[0][0][index].setY(y);
      mPlayerBricks[0][0][index].setWidth(slotWidth);
      mPlayerBricks[0][0][index].setHeight(slotHeight);
      mPlayerBricks[0][0][index].setColor(color);

      mPlayerBricks[0][1][index].setX(x);
      mPlayerBricks[0][1][index].setY(y);
      mPlayerBricks[0][1][index].setWidth(slotWidth);
      mPlayerBricks[0][1][index].setHeight(slotHeight);
      mPlayerBricks[0][1][index].setColor(color);

      mPlayerBricks[1][0][index].setX(x);
      mPlayerBricks[1][0][index].setY(y);
      mPlayerBricks[1][0][index].setWidth(slotWidth);
      mPlayerBricks[1][0][index].setHeight(slotHeight);
      mPlayerBricks[1][0][index].setColor(color);

      mPlayerBricks[1][1][index].setX(x);
      mPlayerBricks[1][1][index].setY(y);
      mPlayerBricks[1][1][index].setWidth(slotWidth);
      mPlayerBricks[1][1][index].setHeight(slotHeight);
      mPlayerBricks[1][1][index].setColor(color);

      x += slotWidth + slotSpacing;
    }
    y += slotHeight + slotSpacing;
  }
}

CourtScene::~CourtScene()
{
  // ...
}

void CourtScene::update(float dt)
{
  mPaddle.update(dt);
  mBall.update(dt);
}

void CourtScene::render()
{
  auto& renderer = mGame.getRenderer();
  mLeftWall.render(renderer);
  mRightWall.render(renderer);
  mTopWall.render(renderer);
  mBall.render(renderer);
  mPaddle.render(renderer);
  mPlayerIndexDigit.render(renderer);
  mPlayerBallIndexDigit.render(renderer);

  // render the bricks for the currently active player and level.
  for (auto i = 0u; i < 112; i++) {
    auto player = (int)mActivePlayer;
    auto level = mPlayerLevel[player];
    mPlayerBricks[player][level][i].render(renderer);
  }

  mPlayerScoreDigits[0][0].render(renderer);
  mPlayerScoreDigits[0][1].render(renderer);
  mPlayerScoreDigits[0][2].render(renderer);
  mPlayerScoreDigits[0][3].render(renderer);

  mPlayerScoreDigits[1][0].render(renderer);
  mPlayerScoreDigits[1][1].render(renderer);
  mPlayerScoreDigits[1][2].render(renderer);
  mPlayerScoreDigits[1][3].render(renderer);
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
      mBall.setVelocity(mBall.getInitialVelocity());
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

void CourtScene::addPlayerScore(Player player, int amount)
{
  mPlayerScore[(int)player] += amount;
  // TODO start blinking score digits.
  // TODO refresh score digits.
}
