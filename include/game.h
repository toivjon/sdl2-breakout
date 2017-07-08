#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

// global namespace forward declarations.
struct SDL_Window;

namespace breakout
{
	class Game final
	{
	public:
    Game() = delete;
    Game(int height, int width);
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();
  private:
    SDL_Window* mWindow;
  };
}

#endif