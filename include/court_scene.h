/*! The court scene for the Breakout game.
 *
 * This is the main game scene where the game simulation will be processed.
 * It contains all the logics required to move game entities and to make the
 * game act as a "game". This is the biggest scene from the two scenes.
 */
#ifndef BREAKOUT_COURT_SCENE_H
#define BREAKOUT_COURT_SCENE_H

#include "ball.h"
#include "digit.h"
#include "entity.h"
#include "drawable.h"
#include "collideable.h"
#include "paddle.h"
#include "scene.h"

#include <array>
#include <vector>

namespace breakout
{
	class CourtScene final : public Scene
	{
	public:
    static const SDL_Color BRICKS_1_FILL_STYLE;
    static const SDL_Color BRICKS_2_FILL_STYLE;
    static const SDL_Color BRICKS_3_FILL_STYLE;
    static const SDL_Color BRICKS_4_FILL_STYLE;

    /** An enumeration for the currently active player index. */
    enum class Player : int {
      PLAYER_1 = 0,
      PLAYER_2 = 1
    };

    CourtScene(Game& game);

    ~CourtScene();

    void update(float dt) override;
    void render() override;
    void enter() override;
    void keyDown(SDL_KeyboardEvent& event) override;
    void keyUp(SDL_KeyboardEvent& event) override;

    const Collideable& getLeftWall() const            { return mLeftWall;             }
    const Collideable& getRightWall() const           { return mRightWall;            }
    const Collideable& getTopWall() const             { return mTopWall;              }
    const Ball& getBall() const                       { return mBall;                 }
    const Paddle& getPaddle() const                   { return mPaddle;               }
    const Collideable& getOutOfBoundsDetector() const { return mOutOfBoundsDetector;  }

    Paddle& getPaddle() { return mPaddle; }

    Player getActivePlayer() const { return mActivePlayer; }
    int getPlayerLevel(Player player) const { return mPlayerLevel[(int)player]; }
    std::vector<Collideable>& getBricks(Player player, int level) { return mPlayerBricks[(int)player][level]; }
    int getPlayerBallIndex(Player player) const { return mPlayerBallIndex[(int)player]; }
    int getPlayerLevelCount(Player player) const { return mPlayerBricks[(int)player].size(); }

    void setActivePlayer(Player activePlayer) { mActivePlayer = activePlayer; }
    void setPlayerLevel(Player player, int level) { mPlayerLevel[(int)player] = level; }
    void setPlayerBallIndex(Player player, int index) { mPlayerBallIndex[(int)player] = index; }

    void addPlayerScore(Player player, int amount);
    void addPlayerLevel(std::vector<Collideable>& level, Player player);
    void incrementBallIndex(Player player);
    void resetBallAndPaddle();
    void endGame();
    void switchPlayer();
  private:
    void refreshScoreDigits(Player player);
    void blinkScoreDigits(Player player);
  private:
    Player             mActivePlayer;
    std::array<int, 2> mPlayerLevel;
    std::array<int, 2> mPlayerScore;
    std::array<int, 2> mPlayerBallIndex;

    Collideable                             mLeftWall;
    Collideable                             mRightWall;
    Collideable                             mTopWall;
    Ball                                    mBall;
    Paddle                                  mPaddle;
    Digit                                   mPlayerIndexDigit;
    Digit                                   mPlayerBallIndexDigit;
    std::vector<std::vector<Digit>>         mPlayerScoreDigits;
    std::vector<std::vector<std::vector<Collideable>>>   mPlayerBricks;
    Collideable                             mOutOfBoundsDetector;
  };
}

#endif