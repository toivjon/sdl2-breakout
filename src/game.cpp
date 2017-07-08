#include "game.h"
#include "welcome_scene.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace breakout;

Game::Game(int height, int width, const std::string& fontPath) : mWindow(nullptr), mRenderer(nullptr), mFont(nullptr), mScene(nullptr), mState(State::NOT_INITED)
{
  // initialize all SDL2 framework systems.
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    return;
  }

  // initialize TTF system for text rendering.
  if (TTF_Init() == -1) {
    std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
    return;
  }

  // create a new window for the application.
  mWindow = SDL_CreateWindow("SDL2 - Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  if (mWindow == nullptr) {
    std::cerr << "Unable to create SDL window: " << SDL_GetError() << std::endl;
    return;
  }

  // create renderer for the application window.
  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
  if (mRenderer == nullptr) {
    std::cerr << "Unable to create SDL renderer: " << SDL_GetError() << std::endl;
    return;
  }

  // initialize the selected font for the application.
  mFont = TTF_OpenFont(fontPath.c_str(), 28);
  if (mFont == nullptr) {
    std::cerr << "Unable to load font: " << TTF_GetError() << std::endl;
    return;
  }

  // check that the game gets inited state flag.
  mState = State::INITED;
}

Game::~Game()
{
  if (mFont != nullptr) {
    TTF_CloseFont(mFont);
  }
  if (mRenderer != nullptr) {
    SDL_DestroyRenderer(mRenderer);
  }
  if (mWindow != nullptr) {
    SDL_DestroyWindow(mWindow);
  }
  TTF_Quit();
  SDL_Quit();
}

void Game::setScene(std::shared_ptr<Scene> scene)
{
  if (scene) {
    // perform a cleanup from the old scene (if any).
    if (mScene) {
      mScene->exit();
    }

    // apply the new scene and call the scene init (reset).
    mScene = scene;
    mScene->enter();
  }
}

int Game::run()
{
  // return with an error code if we do not have a good game state.
  if (mState != State::INITED && mState != State::STOPPED) {
    std::cerr << "Unable to run game as the game state is " << (int)mState << std::endl;
    return -1;
  }

  // set the initial scene for the game.
  setScene(std::make_shared<WelcomeScene>(*this));

  SDL_Event event;
  mState = State::RUNNING;
  while (mState == State::RUNNING) {
    // poll and handle events from the SDL.
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
      case SDL_QUIT:
        mState = State::STOPPED;
        break;
      case SDL_KEYDOWN:
        mScene->keyDown(event.key);
        break;
      case SDL_KEYUP:
        mScene->keyUp(event.key);
        break;
      }
    }

    // clear the rendering context with the black color.
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(mRenderer);

    mScene->update();
    mScene->render();

    // present the rendered buffer.
    SDL_RenderPresent(mRenderer);
  }
  return 0;
}