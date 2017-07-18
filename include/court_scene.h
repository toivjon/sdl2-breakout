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

    CourtScene() = delete;
    CourtScene(Game& game);
    CourtScene(const CourtScene&) = delete;
    CourtScene(CourtScene&&) = delete;

    CourtScene& operator=(const CourtScene&) = delete;
    CourtScene& operator=(CourtScene&&) = delete;

    ~CourtScene();

    void update(float dt) override;
    void render() override;
    void enter() override;
    void keyDown(SDL_KeyboardEvent& event) override;
    void keyUp(SDL_KeyboardEvent& event) override;

    const Collideable& getLeftWall() const  { return mLeftWall;   }
    const Collideable& getRightWall() const { return mRightWall;  }
    const Collideable& getTopWall() const   { return mTopWall;    }
    const Ball& getBall() const             { return mBall;       }
    const Paddle& getPaddle() const         { return mPaddle;     }

    Player getActivePlayer() const { return mActivePlayer; }
    int getPlayerLevel(Player player) const { return mPlayerLevel[(int)player]; }
    std::vector<Collideable>& getBricks(Player player, int level) { return mPlayerBricks[(int)player][level]; }

    void setActivePlayer(Player activePlayer) { mActivePlayer = activePlayer; }
    void setPlayerLevel(Player player, int level) { mPlayerLevel[(int)player] = level; }

    void addPlayerScore(Player player, int amount);
  private:
    Player             mActivePlayer;
    std::array<int, 2> mPlayerLevel;
    std::array<int, 2> mPlayerScore;

    Collideable                             mLeftWall;
    Collideable                             mRightWall;
    Collideable                             mTopWall;
    Ball                                    mBall;
    Paddle                                  mPaddle;
    Digit                                   mPlayerIndexDigit;
    Digit                                   mPlayerBallIndexDigit;
    std::vector<std::vector<Digit>>         mPlayerScoreDigits;
    std::vector<std::vector<std::vector<Collideable>>>   mPlayerBricks;
  };
}

#endif