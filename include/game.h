#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

namespace breakout
{
	class Game final
	{
	public:
    Game();
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();
  private:

  };
}

#endif