#ifndef BREAKOUT_WELCOME_SCENE_H
#define BREAKOUT_WELCOME_SCENE_H

#include "scene.h"

namespace breakout
{
	class WelcomeScene final : public Scene
	{
  public:
    WelcomeScene() = delete;
    WelcomeScene(Game& game);
    WelcomeScene(const WelcomeScene&) = delete;
    WelcomeScene(WelcomeScene&&) = delete;

    WelcomeScene& operator=(const WelcomeScene&) = delete;
    WelcomeScene& operator=(WelcomeScene&&) = delete;

    ~WelcomeScene();

    void update() override;
    void render() override;
    void enter() override;
    void exit() override;
  };
}

#endif