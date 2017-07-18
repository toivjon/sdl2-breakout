/*! The welcoming scene for the Breakout game.
 *
 *  This scene is the main scene which will be shown to users when they open
 *  the game. Our implementation contains a simple view where users see the 
 *  name of the game and an instructions about how to start the game.
 */
#ifndef BREAKOUT_WELCOME_SCENE_H
#define BREAKOUT_WELCOME_SCENE_H

#include "scene.h"

#include <SDL.h>

namespace breakout
{
	class WelcomeScene final : public Scene
	{
  public:
    WelcomeScene(Game& game);

    ~WelcomeScene();

    void update(float dt) override;
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