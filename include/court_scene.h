#ifndef BREAKOUT_COURT_SCENE_H
#define BREAKOUT_COURT_SCENE_H

#include "entity.h"
#include "drawable.h"
#include "collideable.h"
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
  private:
    Collideable mLeftWall;
    Collideable mRightWall;
    Collideable mTopWall;
  };
}

#endif