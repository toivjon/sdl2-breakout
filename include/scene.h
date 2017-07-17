#ifndef BREAKOUT_SCENE_H
#define BREAKOUT_SCENE_H

// global namespace forward declarations.
struct SDL_KeyboardEvent;

namespace breakout
{
  class Game;
  class Scene
  {
  public:
    Scene() = delete;
    Scene(Game& game) : mGame(game) {}
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;

    Scene& operator=(const Scene&) = delete;
    Scene& operator=(Scene&&) = delete;

    virtual ~Scene() {}

    virtual void update(float dt) {}
    virtual void render() {}
    virtual void enter() {}
    virtual void exit() {}
    virtual void keyDown(SDL_KeyboardEvent& event) {}
    virtual void keyUp(SDL_KeyboardEvent& event) {}
  protected:
    Game& mGame;
  };
}

#endif