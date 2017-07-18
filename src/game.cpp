#include "game.h"
#include "welcome_scene.h"

#include <chrono>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <ctime>

using namespace breakout;

inline unsigned long currentMillis()
{
  using namespace std::chrono;
  return (unsigned long) duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Game::Game(int width, int height, const std::string& fontPath)
  : mWindow(nullptr),
    mRenderer(nullptr),
    mFont(nullptr),
    mScene(nullptr),
    mState(State::NOT_INITED),
    mCurrentTickMillis(0l),
    mPreviousTickMillis(0l),
    mDeltaAccumulator(0l)
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
  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

  // initialize random.
  srand((unsigned int)time(NULL));

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
  mPreviousTickMillis = currentMillis();
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

    // calculate the delta between the current and previous tick milliseconds.
    mCurrentTickMillis = currentMillis();
    auto dt = (mCurrentTickMillis - mPreviousTickMillis);
    mPreviousTickMillis = mCurrentTickMillis;
    
    // update game logics with a fixed framerate.
    mDeltaAccumulator += dt;
    static const auto FPS = (1000l / 60l);
    if (mDeltaAccumulator >= FPS) {
      mScene->update(static_cast<float>(FPS));
      mDeltaAccumulator -= FPS;
    }

    // clear the rendering context with the black color.
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(mRenderer);

    // render the scene on the buffer.
    mScene->render();

    // present the rendered buffer.
    SDL_RenderPresent(mRenderer);
  }
  return 0;
}

SDL_Texture* Game::createText(const std::string& text)
{
  // create a surface which contains the desired text.
  SDL_Color color{ 0xff, 0xff, 0xff, 0xff };
  auto surface = TTF_RenderText_Blended(mFont, text.c_str(), color);
  if (surface == nullptr) {
    std::cerr << "Unable to create a surface with a text: " << TTF_GetError() << std::endl;
    return nullptr;
  }

  // create a texture from the text surface.
  auto texture = SDL_CreateTextureFromSurface(mRenderer, surface);
  SDL_FreeSurface(surface);
  if (texture == nullptr) {
    std::cerr << "Unable to create texture from a text surface: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  return texture;
}