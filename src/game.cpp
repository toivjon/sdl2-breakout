#include "game.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace breakout;

Game::Game()
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
}

Game::~Game()
{
  TTF_Quit();
  SDL_Quit();
}