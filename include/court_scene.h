#ifndef BREAKOUT_COURT_SCENE_H
#define BREAKOUT_COURT_SCENE_H

#include "ball.h"
#include "entity.h"
#include "drawable.h"
#include "collideable.h"
#include "paddle.h"
#include "scene.h"

namespace breakout
{
	class CourtScene final : public Scene
	{
	public:
    CourtScene() = delete;
    CourtScene(Game& game);
    CourtScene(const CourtScene&) = delete;
    CourtScene(CourtScene&&) = delete;

    CourtScene& operator=(const CourtScene&) = delete;
    CourtScene& operator=(CourtScene&&) = delete;

    ~CourtScene();

    void update() override;
    void render() override;
    void enter() override;
    void keyDown(SDL_KeyboardEvent& event) override;
    void keyUp(SDL_KeyboardEvent& event) override;

    const Collideable& getLeftWall() const  { return mLeftWall;   }
    const Collideable& getRightWall() const { return mRightWall;  }
    const Collideable& getTopWall() const   { return mTopWall;    }
    const Ball& getBall() const             { return mBall;       }
    const Paddle& getPaddle() const         { return mPaddle;     }
  private:
    Collideable mLeftWall;
    Collideable mRightWall;
    Collideable mTopWall;
    Ball        mBall;
    Paddle      mPaddle;
  };
}

#endif