#include "welcome_scene.h"
#include "court_scene.h"
#include "game.h"

#include <SDL.h>

using namespace breakout;

WelcomeScene::WelcomeScene(Game& game) : Scene(game)
{
  // ...
}

WelcomeScene::~WelcomeScene()
{
  // ...
}

void WelcomeScene::update()
{
  // ...
}

void WelcomeScene::render()
{
  // ...
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
    // TODO mGame.setScene(std::make_shared<CourtScene>(mGame));
    break;
  case SDLK_2:
    mGame.setPlayMode(Game::PlayMode::TWO_PLAYERS);
    // TODO mGame.setScene(std::make_shared<CourtScene>(mGame));
    break;
  }
}