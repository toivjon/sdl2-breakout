#include "game.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace breakout;

Game::Game(int height, int width) : mWindow(nullptr)
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
}

Game::~Game()
{
  if (mWindow != nullptr) {
    SDL_DestroyWindow(mWindow);
  }
  TTF_Quit();
  SDL_Quit();
}