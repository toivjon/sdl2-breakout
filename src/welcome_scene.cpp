#include "welcome_scene.h"
#include "court_scene.h"
#include "game.h"

#include <SDL.h>

using namespace breakout;

WelcomeScene::WelcomeScene(Game& game)
  : Scene(game),
    mTopicText(nullptr),
    mControlsText(nullptr),
    mSpacebarText(nullptr),
    mLeftArrowText(nullptr),
    mRightArrowText(nullptr),
    mOnePlayerGameText(nullptr),
    mTwoPlayerGameText(nullptr)
{
  // construct text textures used to render textual contents.
  mTopicText = mGame.createText("SDL2 BREAKOUT");
  mControlsText = mGame.createText("Controls:");
  mSpacebarText = mGame.createText("[spacebar] launch a ball");
  mLeftArrowText = mGame.createText("[left-arrow] move left");
  mRightArrowText = mGame.createText("[right-arrow] move right");
  mOnePlayerGameText = mGame.createText("Press [1] to start a 1 player game");
  mTwoPlayerGameText = mGame.createText("Press [2] to start a 2 player game");

  // query texture dimensions for each text texture.
  SDL_QueryTexture(mTopicText, nullptr, nullptr, &mTopicTextPosition.w, &mTopicTextPosition.h);
  SDL_QueryTexture(mControlsText, nullptr, nullptr, &mControlTextPosition.w, &mControlTextPosition.h);
  SDL_QueryTexture(mSpacebarText, nullptr, nullptr, &mSpacebarTextPosition.w, &mSpacebarTextPosition.h);
  SDL_QueryTexture(mLeftArrowText, nullptr, nullptr, &mLeftArrowTextPosition.w, &mLeftArrowTextPosition.h);
  SDL_QueryTexture(mRightArrowText, nullptr, nullptr, &mRightArrowTextPosition.w, &mRightArrowTextPosition.h);
  SDL_QueryTexture(mOnePlayerGameText, nullptr, nullptr, &mOnePlayerGameTextPosition.w, &mOnePlayerGameTextPosition.h);
  SDL_QueryTexture(mTwoPlayerGameText, nullptr, nullptr, &mTwoPlayerGameTextPosition.w, &mTwoPlayerGameTextPosition.h);

  // get the rendering window size and calculate the center position.
  int windowWidth = 0, windowHeight = 0;
  SDL_GetWindowSize(mGame.getWindow(), &windowWidth, &windowHeight);
  int windowCenterX = (windowWidth / 2);

  // assign texts at the center of the screen.
  #define CENTER(rect) (rect.x = windowCenterX - (rect.w / 2));
  CENTER(mTopicTextPosition);
  CENTER(mControlTextPosition);
  CENTER(mSpacebarTextPosition);
  CENTER(mLeftArrowTextPosition);
  CENTER(mRightArrowTextPosition);
  CENTER(mOnePlayerGameTextPosition);
  CENTER(mTwoPlayerGameTextPosition);

  // assign vertical positions for each texture.
  int slotHeight = (windowHeight / 10);
  mTopicTextPosition.y = slotHeight;
  mControlTextPosition.y = static_cast<int>(2.5 * slotHeight);
  mSpacebarTextPosition.y = (3 * slotHeight);
  mLeftArrowTextPosition.y = static_cast<int>(3.5 * slotHeight);
  mRightArrowTextPosition.y = (4 * slotHeight);
  mOnePlayerGameTextPosition.y = (6 * slotHeight);
  mTwoPlayerGameTextPosition.y = (7 * slotHeight);
}

WelcomeScene::~WelcomeScene()
{
  // define a helper function to be used to release textures.
  #define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }

  // release all reserved textures.
  RELEASE_TEXTURE(mTopicText);
  RELEASE_TEXTURE(mControlsText);
  RELEASE_TEXTURE(mSpacebarText);
  RELEASE_TEXTURE(mLeftArrowText);
  RELEASE_TEXTURE(mRightArrowText);
  RELEASE_TEXTURE(mOnePlayerGameText);
  RELEASE_TEXTURE(mTwoPlayerGameText);
}

void WelcomeScene::update(float dt)
{
  // ...
}

void WelcomeScene::render()
{
  // get a reference to the SDL renderer.
  auto& renderer = mGame.getRenderer();

  // draw all texts on the buffer.
  SDL_RenderCopy(&renderer, mTopicText, nullptr, &mTopicTextPosition);
  SDL_RenderCopy(&renderer, mControlsText, nullptr, &mControlTextPosition);
  SDL_RenderCopy(&renderer, mSpacebarText, nullptr, &mSpacebarTextPosition);
  SDL_RenderCopy(&renderer, mLeftArrowText, nullptr, &mLeftArrowTextPosition);
  SDL_RenderCopy(&renderer, mRightArrowText, nullptr, &mRightArrowTextPosition);
  SDL_RenderCopy(&renderer, mOnePlayerGameText, nullptr, &mOnePlayerGameTextPosition);
  SDL_RenderCopy(&renderer, mTwoPlayerGameText, nullptr, &mTwoPlayerGameTextPosition);
}

void WelcomeScene::enter()
{
  // ...
}

void WelcomeScene::exit()
{
  // ...
}

void WelcomeScene::keyUp(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_1:
    mGame.setPlayMode(Game::PlayMode::SINGLE_PLAYER);
    mGame.setScene(std::make_shared<CourtScene>(mGame));
    break;
  case SDLK_2:
    mGame.setPlayMode(Game::PlayMode::TWO_PLAYERS);
    mGame.setScene(std::make_shared<CourtScene>(mGame));
    break;
  }
}