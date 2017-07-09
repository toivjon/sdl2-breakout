#ifndef BREAKOUT_WELCOME_SCENE_H
#define BREAKOUT_WELCOME_SCENE_H

#include "scene.h"

#include <SDL.h>

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
    void keyUp(SDL_KeyboardEvent& event);
  private:
    SDL_Texture* mTopicText;
    SDL_Texture* mControlsText;
    SDL_Texture* mSpacebarText;
    SDL_Texture* mLeftArrowText;
    SDL_Texture* mRightArrowText;
    SDL_Texture* mOnePlayerGameText;
    SDL_Texture* mTwoPlayerGameText;

    SDL_Rect mTopicTextPosition;
    SDL_Rect mControlTextPosition;
    SDL_Rect mSpacebarTextPosition;
    SDL_Rect mLeftArrowTextPosition;
    SDL_Rect mRightArrowTextPosition;
    SDL_Rect mOnePlayerGameTextPosition;
    SDL_Rect mTwoPlayerGameTextPosition;
  };
}

#endif