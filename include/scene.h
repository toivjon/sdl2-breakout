#ifndef BREAKOUT_SCENE_H
#define BREAKOUT_SCENE_H

// global namespace forward declarations.
struct SDL_KeyboardEvent;

namespace breakout
{
  class Scene
  {
  public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void keyDown(SDL_KeyboardEvent& event) = 0;
    virtual void keyUp(SDL_KeyboardEvent& event) = 0;
  };
}

#endif