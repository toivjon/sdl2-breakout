#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <string>

// global namespace forward declarations.
struct SDL_Window;
struct SDL_Renderer;
struct _TTF_Font;

namespace breakout
{
	class Game final
	{
	public:
    Game() = delete;
    Game(int height, int width, const std::string& fontPath);
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();
  private:
    SDL_Window*   mWindow;
    SDL_Renderer* mRenderer;
    _TTF_Font*    mFont;
  };
}

#endif