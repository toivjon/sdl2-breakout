#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include "scene.h"

#include <memory>
#include <string>

// global namespace forward declarations.
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

namespace breakout
{
	class Game final
	{
	public:
    enum class State { NOT_INITED, INITED, RUNNING, STOPPED };
    enum class PlayMode { SINGLE_PLAYER, TWO_PLAYERS };

    Game() = delete;
    Game(int width, int height, const std::string& fontPath);
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();

    void setScene(std::shared_ptr<Scene> scene);

    int run();

    SDL_Texture* createText(const std::string& text);

    PlayMode getPlayMode() const { return mPlayMode; }
    void setPlayMode(PlayMode playMode) { mPlayMode = playMode; }

    SDL_Renderer& getRenderer() const { return *mRenderer; }

    SDL_Window* getWindow() const { return mWindow; }
  private:
    SDL_Window*             mWindow;
    SDL_Renderer*           mRenderer;
    _TTF_Font*              mFont;
    std::shared_ptr<Scene>  mScene;
    State                   mState;
    PlayMode                mPlayMode;
  };
}

#endif