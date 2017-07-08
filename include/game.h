#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include "scene.h"

#include <memory>
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
    enum class State { NOT_INITED, INITED, RUNNING, STOPPED };

    Game() = delete;
    Game(int height, int width, const std::string& fontPath);
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();

    void setScene(std::shared_ptr<Scene> scene);

    int run();
  private:
    SDL_Window*             mWindow;
    SDL_Renderer*           mRenderer;
    _TTF_Font*              mFont;
    std::shared_ptr<Scene>  mScene;
    State                   mState;
  };
}

#endif